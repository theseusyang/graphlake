#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "edges.h"

status_t 
labeled_edges_t::initial_setup(degree_t a_degree)
{
	degree = a_degree;
	return 0;
}

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
kbtree_t::split_leaf(kleaf_node_t* leaf_node1, key_t key)
{
	int				count		= leaf_node1->count;
	kleaf_node_t*	leaf_node2	= (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
	
	leaf_node2->sorted = 1;
	
	kinner_node_t* tmp_inner_node = (kinner_node_t*) malloc(sizeof(kinner_node_t));
	tmp_inner_node->count = 0;
	//assert(leaf_node1->count == count);
	
	int i = 0;
	while (key > leaf_node1->keys[i] && i < count) {
		++i;
	}

	//Lets break the first leaf in half
	int half = (count >> 1);
	if ( i <= half) { //If new key in the first half
		memcpy(leaf_node2->keys, leaf_node1->keys + half, (count - half)*sizeof(key_t));
		leaf_node2->count = count - half;

		memmove(leaf_node1->keys + i+1, leaf_node1->keys + i, (half - i)*sizeof(key_t));
		leaf_node1->keys[i] = key;
		leaf_node1->count = half + 1;

	} else {//new key in second half
		memcpy(leaf_node2->keys, leaf_node1->keys + half, (i-half)*sizeof(key_t));
		leaf_node2->keys[i-half] = key;
		memcpy(leaf_node2->keys + i - half + 1, leaf_node1->keys + i, (count - i)*sizeof(key_t));
		leaf_node2->count = count - half + 1;
		
		leaf_node1->count = half;
		
	}

	//establish the sibling relationship
	leaf_node1->next = leaf_node2;

	//setup the higher level keys and pointers
	tmp_inner_node->keys[0] = leaf_node2->keys[0];
	tmp_inner_node->count += 1;
	
	tmp_inner_node->values[0] = leaf_node1;
	tmp_inner_node->values[1] = leaf_node2;
	
	//set up the hihger node pointers
	btree.inner_node = tmp_inner_node;
	
	return 0;
}

void 
kbtree_t::insert_in_leaf(kleaf_node_t* leaf_node1, key_t key)
{
	int		count = leaf_node1->count;
	int		i	  = 0;
	assert(count < kleaf_keys);
	
	while (key > leaf_node1->keys[i] && i < count) {
		++i;
	}
	memmove(leaf_node1 + i + 1, leaf_node1 + i, (count - i )*sizeof(key_t));
	leaf_node1->keys[i] = key;
	leaf_node1->count += 1;

	return;
}

void kbtree_t::insert_inplace(key_t key)
{	int count = degree;
	int i	  = 0;
	assert(count < kinplace_keys);

	while (key > inplace_keys[i]&& i < count) {
		++i;
	}
	memmove(inplace_keys + i + 1, inplace_keys + i, (count - i)*sizeof(key_t));
	inplace_keys[i] = key;

	//increment will be done in caller function.
	return ;
}
status_t 
kbtree_t::insert(key_t key)
{
	int count = degree;
	++degree;

	if (count < inplace_knode) {
	} else if (count < kleaf_keys) {
		insert_in_leaf(btree.leaf_node, key);
	} else if (count == kleaf_keys) {
		split_leaf(btree.leaf_node, key);
	} else {//Some hihger level node already exists
		/*
		tmp_inner_node = btree.inner_node;
		unsigned int i = 0;
		while (key < tmp_inner_node->keys[i] && i < tmp_inner_node->count) {
			++i;
		}
		*/
	}
	++degree;
	return 0;
}
