#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

#include "kbtree.h"

using std::min;

kinner_node_t*
create_higher_inner_node(kinner_node_t** inner_node, int count, int level)
{
	int level_count = 1; 
	if (count > kinner_values) {
		level_count = count/kinner_values + (0!= level_count % kinner_values);
	}
		
	kinner_node_t* tmp_node = 0;

	if (level_count > 1) {
		kinner_node_t** higher_inner_node = (kinner_node_t**)calloc(
							sizeof(kinner_node_t*), level_count); 
		int k = 0;
		for (int i = 0; i < level_count - 1; ++i) {
			tmp_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			tmp_node->level = level;
			for (int j = 0; j < kinner_values; ++j) {
				tmp_node->values[j] = (void*)inner_node[k++];
			}
			higher_inner_node[i] = tmp_node;
		}
		//last higher node.
		tmp_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
		tmp_node->level = level;
		for (int j = 0; k < count; ++k, ++j) {
			tmp_node->values[j] = (void*)inner_node[k];
		}
		higher_inner_node[level_count - 1] = tmp_node;

		//XXX
		tmp_node = create_higher_inner_node(higher_inner_node, level_count, level+1);
		free(higher_inner_node);
		return tmp_node;

	} else {//just one node
		tmp_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
		tmp_node->level = level;
		for (int k = 0; k < count; ++k) {
			tmp_node->values[k] = (void*)inner_node[k];
		}
		return tmp_node;	
	}
}

status_t 
kbtree_t::initial_setup(degree_t a_degree)
{
	degree = a_degree;
	if (degree <=2 ) return 0;
	else if (degree <= kleaf_keys) {
		btree.leaf_node = (kleaf_node_t*)calloc(sizeof(kleaf_node_t), degree);
		return 0;
	}

	//Degree count decides the level of b-tree.
	int leafnode_count = a_degree/kleaf_keys + (0!= (a_degree % kleaf_keys));
	//edges_tree = (kbtree_t*)malloc(sizeof(kbtree_t));
	kinner_node_t* inner_node = 0;
	
	int level = 1;	
	
	int level_count = 1;
	if (leafnode_count > kinner_values) {
		level_count = level_count/kinner_values 
				+ (0 != level_count % kinner_values);
	}
	kinner_node_t* node = 0; 

	if (level_count > 1) {
		kinner_node_t** higher_inner_node = (kinner_node_t**)calloc(
							sizeof(kinner_node_t*), level_count);

		for (int m = 0; m < level_count -1; ++m) {
			node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			node->level = level;
			for (int n = 0; n < leafnode_count; ++n) {
				node->values[n] = malloc(sizeof(kleaf_node_t));
			}
			higher_inner_node[m] = node; 
		}
		//last higher node
		node = (kinner_node_t*)malloc( sizeof(kinner_node_t));
		node->level = level;
		for (int n = 0; n < leafnode_count; ++n) {
			node->values[n] = malloc(sizeof(kleaf_node_t));
		}
		higher_inner_node[level_count-1] = node;
		
		//XXX
		inner_node = create_higher_inner_node(higher_inner_node, level_count, level+1);
		free(higher_inner_node);
	} else {
		kinner_node_t* node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
		node->level = level;
		for (int n = 0; n < leafnode_count; ++n) {
			node->values[n] = malloc(sizeof(kleaf_node_t));
		}
		inner_node = node;
	}
		
	btree.inner_node = inner_node;
	//btree.leaf_node_node = 0;

	return 0;
}

status_t 
kbtree_t::split_leaf(kleaf_node_t* leaf_node1, key_t key, split_info_t* split_info)
{
	int				count		= leaf_node1->count;
	kleaf_node_t*	leaf_node2	= (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
	
	leaf_node2->sorted = 1;
	
	//assert(leaf_node1->count == count);
	
	int i = 0;
	while (i < count && key > leaf_node1->keys[i]) {
		++i;
	}

	if (i < count && leaf_node1->keys[i] == key) {
		return keyExist;
	}

	//Lets break the first leaf in half
	int half = (count >> 1);
	if ( i <= half) { //If new key in the first half
		memcpy(leaf_node2->keys, leaf_node1->keys + half, (count - half)*sizeof(key_t));
		leaf_node2->count = count - half;

		memmove(leaf_node1->keys + i+1, leaf_node1->keys + i, (half - i)*sizeof(key_t));
		leaf_node1->keys[i] = key;
		leaf_node1->count = half + 1;

	} else { //new key in second half
		memcpy(leaf_node2->keys, leaf_node1->keys + half, (i-half)*sizeof(key_t));
		leaf_node2->keys[i-half] = key;
		memcpy(leaf_node2->keys + i - half + 1, leaf_node1->keys + i, (count - i)*sizeof(key_t));
		leaf_node2->count = count - half + 1;
		
		leaf_node1->count = half;
	}

	//establish the sibling relationship
	//leaf_node2->next = leaf_node1->next;
	//leaf_node1->next = leaf_node2;

	split_info->key = leaf_node2->keys[0];
	split_info->value = leaf_node2;

	return 0;
}

status_t 
kbtree_t::insert_in_leaf(kleaf_node_t* leaf_node1, key_t key)
{
	int		count = leaf_node1->count;
	int		i	  = 0;
	assert(count < kleaf_keys);
	
	while (i < count && key > leaf_node1->keys[i]) {
		++i;
	}
	if (i < count && leaf_node1->keys[i] == key) {
		return keyExist;
	}

	memmove(leaf_node1 + i + 1, leaf_node1 + i, (count - i )*sizeof(key_t));
	leaf_node1->keys[i] = key;
	leaf_node1->count += 1;
	unused = min(unused, key);

	return 0;
}

status_t 
kbtree_t::insert_inplace(key_t key)
{	
	int count = degree;
	int i	  = 0;
	key_t min_key = key;
	
	if (count == 0) {
		unused = key;
		btree.inplace_keys[0] = key;
	} else if (count == 1) {
		if (unused == key) {
			return keyExist;
		} else {
			btree.inplace_keys[1] = key;
			unused = min(unused, key);
		}
	} else { //time to split
		return split_inplace(key);
	}

	return 0;
}

status_t 
kbtree_t::split_inplace(key_t key) 
{
	int count = degree;
	int i = 0;
	while(i < count && key > btree.inplace_keys[i]) {
		++i;
	}
	if (i < count && key == btree.inplace_keys[i]) {
		return keyExist;
	}
	
	kleaf_node_t* leaf_node = (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
	leaf_node->count = degree + 1;
	leaf_node->sorted = 1;
	memcpy(leaf_node->keys, btree.inplace_keys, i*sizeof(key_t));
	leaf_node->keys[i] = key;
	memcpy(leaf_node->keys + i + 1, btree.inplace_keys + i, (degree - i)*sizeof(key_t));
	btree.leaf_node = leaf_node;
	unused = min(unused, key);
	return 0;
}

//second argument is in/out both
status_t
kbtree_t::split_innernode(kinner_node_t* inner_node1, int i, split_info_t* split_info)
{
	kinner_node_t* inner_node2 = (kinner_node_t*)malloc(sizeof(kinner_node_t));
	inner_node2->level = inner_node1->level;

	int count = inner_node1->count;
	key_t key = split_info->key;
	void* value = split_info->value;
	
	//Lets break the first leaf in half
	int half = (count >> 1);
	if (i <= half) { //If new key in the first half
		memcpy(inner_node2->keys, inner_node1->keys + half, (count - half)*sizeof(key_t));
		memcpy(inner_node2->values, inner_node1->values + half, (count - half)*sizeof(void*));
		inner_node2->count = count - half;

		memmove(inner_node1->keys + i+1, inner_node1->keys + i, (half - i)*sizeof(key_t));
		memmove(inner_node1->values + i+1, inner_node1->values + i, (half - i)*sizeof(void*));
		inner_node1->keys[i] = key;
		inner_node1->values[i] = value;
		inner_node1->count = half + 1;

	} else {//new key in second half
		memcpy(inner_node2->keys, inner_node1->keys + half, (i-half)*sizeof(key_t));
		memcpy(inner_node2->values, inner_node1->values + half, (i-half)*sizeof(void*));
		inner_node2->keys[i-half] = key;
		inner_node2->values[i-half] = value;
		memcpy(inner_node2->keys + i - half + 1, inner_node1->keys + i, (count - i)*sizeof(key_t));
		memcpy(inner_node2->values + i - half + 1, inner_node1->values + i, (count - i)*sizeof(void*));
		inner_node2->count = count - half + 1;
		
		inner_node1->count = half;
	}

	//link the nodes



	return 0;
}

status_t 
kbtree_t::insert_traverse(kinner_node_t* root, key_t key)
{
	status_t ret = 0;
	kinner_node_t*	tmp_inner_node = root;
	traverse_info	kstack[8];

	int		level	= tmp_inner_node->level;
	int		top		= 0;
	int		i		= 1;

	while (level >= 1) {
		//inner node scanning
		while (i < tmp_inner_node->count && key >= tmp_inner_node->keys[i]) {
			++i;
		}

		--i;
		if (key == tmp_inner_node->keys[i]) return keyExist;

		kstack[top].inner_node = tmp_inner_node;
		kstack[top].i = i;
		tmp_inner_node = (kinner_node_t*)tmp_inner_node->values[i];
		++top;
		--level;
		i = 1;
	}
	
	//Now we have leaf node with us.
	kleaf_node_t* leaf_node = (kleaf_node_t*)(tmp_inner_node);
	int			  key_count = leaf_node->count;
	
	if (key_count == kleaf_keys) {
		split_info_t split_info;
		int count = 0;
		if (0 != (ret = split_leaf(leaf_node, key, &split_info))) return ret;
		
		//XXX
		while (top > 0) {
			--top;
			tmp_inner_node = (kinner_node_t*)kstack[top].inner_node;
			i = kstack[top].i;
			count = tmp_inner_node->count;
			if (count == kinner_keys) { //split this higher node as well.
				split_innernode(tmp_inner_node, i, &split_info);

			} else { //insert the new key in the higher node
				memmove(tmp_inner_node->keys + i + 1, tmp_inner_node->keys + i, (count - i)*sizeof(key_t));
				memmove(tmp_inner_node->values + i + 1, tmp_inner_node->values + i, (count - i)*sizeof(void*));
				tmp_inner_node->keys[i] = split_info.key;
				tmp_inner_node->values[i] = split_info.value;
				return 0;
			}
		}
		//If we did not return above, we need to create an additional level now
		kinner_node_t* new_root = (kinner_node_t*) malloc(sizeof(kinner_node_t));
		
		new_root->count = 1;
		new_root->level = 1;
		new_root->keys[0] = btree.inner_node->keys[0];
		new_root->values[0] = btree.inner_node;
		new_root->keys[1] = split_info.key;
		new_root->values[1] = split_info.value;
		
		//set up the hihger node pointers
		btree.inner_node = new_root;
		return 0;

	} 
	
	return insert_in_leaf(leaf_node, key);
}

status_t 
kbtree_t::insert(key_t key)
{
	int count = degree;
	status_t ret = 0;

	if (count < kinline_keys) {
		ret = insert_inplace(key);
	} else if (count < kleaf_keys) {
		ret = insert_in_leaf(btree.leaf_node, key);
	} else if (count == kleaf_keys) {
		split_info_t split_info;
		if (0 != (ret = split_leaf(btree.leaf_node, key, &split_info))) return ret;
	
		//setup the higher level keys and pointers
		kinner_node_t* tmp_inner_node = (kinner_node_t*) malloc(sizeof(kinner_node_t));
		
		tmp_inner_node->count = 1;
		tmp_inner_node->level = 1;
		tmp_inner_node->keys[0] = btree.leaf_node->keys[0];
		tmp_inner_node->keys[1] = split_info.key;
		tmp_inner_node->values[0] = btree.leaf_node;
		tmp_inner_node->values[1] = split_info.value;
		
		//set up the hihger node pointers
		btree.inner_node = tmp_inner_node;
		ret = 0;
	
	} else {//Some hihger level node already exists
		ret = insert_traverse(btree.inner_node, key);
	}

	degree += (ret == 0);
	return 0;
}
    
//zero return means found.
status_t
kbtree_t::search(key_t key)
{
	int count = degree;
	int		i = 0;

	if (count <= kinline_keys) {
		while (i < count && key > btree.inplace_keys[i]) {
			++i;
		}
		return !(key == btree.inplace_keys[i]);

	} else if (count <= kleaf_keys) {
		//Now we have leaf node with us.
		kleaf_node_t* leaf_node = btree.leaf_node;
		int			  key_count = leaf_node->count;
		
		while (i < key_count && key > leaf_node->keys[i]) {
			++i;
		}
		return !(key == leaf_node->keys[i]);
	} else {
		kinner_node_t*	tmp_inner_node = btree.inner_node;
		int		level	= tmp_inner_node->level;
				
		i = 0;
		while (level >= 1) {
			//inner node scanning
			while (i < tmp_inner_node->count && key >= tmp_inner_node->keys[i]) {
				++i;
			}
			
			if (i == 0 && key < tmp_inner_node->keys[i]) return keyNotFound;
			
			//in case, above loop just keeps executing, 
			//we will be having i = count, so -- needed
			//Also, due to our key structures, we need to do -- for other cases.
			--i;
			if (key == tmp_inner_node->keys[i]) return 0;

			tmp_inner_node = (kinner_node_t*)tmp_inner_node->values[i];
			--level;
			i = 0;
		}
		
		//Now we have leaf node with us.
		kleaf_node_t* leaf_node = (kleaf_node_t*)(tmp_inner_node);
		int			  key_count = leaf_node->count;
		
		//leaf node scanning
		while (i < key_count && key > leaf_node->keys[i]) {
			++i;
		}
		return !(key == leaf_node->keys[i]);
	}
}

int kbtree_t::intersection(kbtree_t* btree1, kbtree_t* btree2)
{
	//We will order by degree.
	//Lower degree will become LEFT, higher degree will RIGHT
	int decide = 
			(btree1->degree <= kinline_keys && 0 < btree1->degree) 
			+ ((btree1->degree <= kleaf_keys && kinline_keys < btree1->degree) << 1)
			+ ((kleaf_keys < btree1->degree)<< 2)
			
			+ ((btree2->degree <= kinline_keys && 0 < btree2->degree) << 3) 
			+ ((btree2->degree <= kleaf_keys && kinline_keys < btree2->degree) << 4)
			+ ((kleaf_keys < btree2->degree)<< 5);

	switch(decide) {
		case 0:
		case 1:
		case 2:
		case 4:
		case 8:
			return 0;
		case 9:
			btree1->intersection00(btree2);
			break;

		case 10:
			btree2->intersection01(btree1);
			break;
		
		case 12:
			btree2->intersection02(btree1);
			break;
		
		case 16:
			return 0;
		
		case 17:
			btree1->intersection01(btree2);
			break;
		
		case 18:
			btree1->intersection11(btree2);
			break;
		
		case 20:
			btree2->intersection12(btree1);
			break;

		case 32:
			return 0;
		
		case 33:
			btree1->intersection02(btree2);
			break;

		case 34:
			btree1->intersection12(btree2);
			break;

		case 36:
			btree1->intersection22(btree2);
		default:
			assert(0);
	}
}

int kbtree_t::intersection_leaf_leaf(degree_t count1, degree_t count2, 
									 key_t* keys1, key_t* keys2)
{
	degree_t iter1	= 0;
	degree_t iter2	= 0;
	int		common	= 0;
	key_t	key1;
	key_t	key2;
	
	while (iter1 < count1 && iter2 < count2) {
		key1 = keys1[iter1];
		key2 = keys2[iter2];
		iter1 += (key1 <= key2);
		iter2 += (key1 >= key2);
		common += (key1 == key2);
	}
	return common;
}

int kbtree_t::intersection00(kbtree_t* btree2)
{
	key_t* keys1	= btree.inplace_keys;
	key_t* keys2	= btree2->btree.inplace_keys;
	degree_t count1 = degree;
	degree_t count2 = btree2->degree;
	return intersection_leaf_leaf(count1, count2, keys1, keys2);
}

int kbtree_t::intersection01(kbtree_t* btree2)
{
	key_t* keys1	= btree.inplace_keys;
	key_t* keys2	= btree2->btree.leaf_node->keys;
	degree_t count1 = degree;
	degree_t count2 = btree2->btree.leaf_node->count;
	return intersection_leaf_leaf(count1, count2, keys1, keys2);
}

int kbtree_t::intersection11(kbtree_t* btree2)
{
	key_t* keys1	= btree.leaf_node->keys;
	key_t* keys2	= btree2->btree.leaf_node->keys;
	degree_t count1 = btree.leaf_node->count;
	degree_t count2 = btree2->btree.leaf_node->count;
	degree_t iter1	= 0;
	degree_t iter2	= 0;
	return intersection_leaf_leaf(count1, count2, keys1, keys2);
}

int kbtree_t::intersection02(kbtree_t* btree2)
{
	key_t* keys1	= btree.inplace_keys;
	degree_t count1 = degree;
	return intersection_leaf_inner(count1, keys1, btree2);
}

int kbtree_t::intersection12(kbtree_t* btree2)
{
	key_t* keys1	= btree.leaf_node->keys;
	degree_t count1 = btree.leaf_node->count;
	return intersection_leaf_inner(count1, keys1, btree2);
}

int kbtree_t::intersection_leaf_inner(degree_t count1,
									 key_t* keys1, kbtree_t* btree2)
{
	degree_t iter1	= 0;
	key_t	key1	= keys1[iter1];
	
	key_t* keys2	= 0;
	degree_t count2 = 0;
	degree_t iter2	= 0;
	
	kinner_node_t* tmp_inner_node = btree2->btree.inner_node;
	kleaf_node_t*  leaf_node  = 0;
	traverse_info	kstack[8];
	
	int	common	= 0;
	int top		= 0;
	int	i		= 1;
	int level	= tmp_inner_node->level;
	key_t	key;	
	
	while (iter1 < count1) {
		key1	= keys1[iter1];
		
		//Rest of the Search
		//Search in reverse order in the kstack to avoid repeating
		while (top > 0) {
			--top;
			tmp_inner_node = (kinner_node_t*) kstack[top].inner_node;
			i	= kstack[top].i;
			key = kstack[top].key;

			if (i+1 >= tmp_inner_node->count || key1 > key) {
				--top;
				continue;
			}

			assert (key1 < key);  //we are good.
			++top; //Keep the last one, because we are good
			level = tmp_inner_node->level -1; // Child's level
			tmp_inner_node = (kinner_node_t*)tmp_inner_node->values[i];
		}
	
		while (level >= 1) {
			iter2 = 0;
			//inner node scanning
			keys2	= tmp_inner_node->keys;
			count2	= tmp_inner_node->count;
			while (i < count2 && key1 >= keys2[i]) {
				++i;
			}
			
			//in case, above loop just keeps executing, 
			//we will be having i = count, so -- needed
			//Also, due to our key structures, we need to do -- for other cases.
			--i;
			if (i == 0 && key1 < keys2[i]) return keyNotFound;
			if (key1 == keys2[i]) {
				++common;
				++iter1;
				continue;
			}

			kstack[top].inner_node = tmp_inner_node;
			//This overflow is fine.
			kstack[top].key		   = keys2[i+1];
			kstack[top].i		   = i;

			tmp_inner_node = (kinner_node_t*)tmp_inner_node->values[i];
			++top;
			--level;
			i = 1;
		}

		//Leaf Search
		leaf_node = (kleaf_node_t*) (tmp_inner_node);
		keys2	= leaf_node->keys;
		count2	= leaf_node->count;
		//iter2	= 0; //Has been setup above
		
		while (iter2 < count2 && key1 >= keys2[iter2]) {
			common += (key1 == keys2[iter2]);
			++iter2;
		}

		++iter1;
	}	
	
	return common;
}

int kbtree_t::intersection22(kbtree_t* btree2)
{
	key_t	key1;
	

	degree_t count1 = 0;
	degree_t count2 = 0;
	
	degree_t iter1	= 0;
	degree_t iter2	= 0;
	
	kinner_node_t* inner_node1 = btree2->btree.inner_node;
	kinner_node_t* inner_node2 = btree2->btree.inner_node;
	kleaf_node_t*  leaf_node1  = 0;
	kleaf_node_t*  leaf_node2  = 0;

	traverse_info	kstack1[8];
	traverse_info	kstack2[8];
	int top1	= 0;
	int top2	= 0;
	
	int	common	= 0;
	int	i		= 1;
	int leve1l	= inner_node1->level;
	int level2	= inner_node2->level;
	
	key_t* keys1	= inner_node1->keys;
	key_t* keys2	= inner_node2->keys;
	
	key_t	key;	
	
	while (iter1 < count1 - 1 && iter2 < count2 - 1) {
		key1	= keys1[iter1];
		key2	= keys2[iter2];

		if (key1 == key2) { //case 0
		} else if (key1 < key2 && next_key1 > key2) {//case 1
		} else if (key2 < key1 && next_key2 > key1) {//case 2
		} else {
			iter1 += (key1 <= key2);
			iter2 += (key2 <= key1);	
		}
	}

	if ( iter1 == count1 -1 ) {
		key1 = keys1[iter1];
		while (iter2 < count2 ) {
			key2 = keys2[iter2];
			if (key1 >= key2) {//case4_1, priv_key2 till key2
			}
			++iter2;
		}
	} else {
		key2 = keys2[iter2];
		while (iter1 < count1) {
			key1 = keys1[iter1];
			if (key2 >=	key1) {//case 4_2, prev_key1 till key1
			}
		}
	}

	return common;
}
