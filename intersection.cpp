#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
#include "kbtree.h"

static int
intersection_leaf_leaf(degree_t count1, degree_t count2, 
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

static int
intersection_leaf_inner(degree_t count1,
					 key_t* keys1, kbtree_t* btree2)
{
	degree_t iter1	= 0;
	key_t	key1	= keys1[iter1];
	
	key_t* keys2	= 0;
	degree_t count2 = 0;
	degree_t iter2	= 0;
	
	kinner_node_t*	tmp_inner_node	= btree2->btree.inner_node;
	kleaf_node_t*	leaf_node		= 0;
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
	
		while (level > 0) {
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
			if ((key1 < keys2[i]) || (key1 == keys2[i])) { // 0th index and equal
				common += (key1 == keys2[i]);
				break;//XXX
			}
			
			kstack[top].inner_node = tmp_inner_node;
			//This overflow is fine.
			kstack[top].key		   = keys2[i+1];
			kstack[top].i		   = i;

			++top;
			--level;
			i = 1;
			iter2 = 0;
		}

		//Leaf Search
		if (0 == level) {
			leaf_node = (kleaf_node_t*) (tmp_inner_node);
			keys2	= leaf_node->keys;
			count2	= leaf_node->count;
			//iter2	= 0; //Has been setup above
			
			while (iter2 < count2 && key1 >= keys2[iter2]) {
				common += (key1 == keys2[iter2]);
				++iter2;
			}

		}
		++iter1;
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
/*
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
*/
//@	which_iter:	1 means return iter for LHS series, 0 means RHS series
static int
intersection_inner_inner(int level, void* node1, void* node2, key_t max1, key_t max2,
						 int which_iter, degree_t& past_iter, int& done)
{

	key_t*		keys1;
	key_t*		keys2;
	degree_t	count1;
	degree_t	count2;
	
	key_t		key1;
	key_t		key2;
	key_t		next_key1;
	key_t		next_key2;
	
	degree_t	iter1	= past_iter;
	degree_t	iter2	= 0;


	//XXX use it to terminate early in the right side comparison 
	degree_t	next_iter = 0;	//will apply to LHS iter
	
	degree_t	prev_iter = 0; //will apply to LHS iter
	
	int common = 0;
	int new_level = level - 1;
	
	//inner handling
	if (level > 0) {
		kinner_node_t* inner_node1 = (kinner_node_t*) node1;
		kinner_node_t* inner_node2 = (kinner_node_t*) node2;

		keys1	= inner_node1->keys;
		keys2	= inner_node2->keys;
		count1  = inner_node1->count;
		count2	= inner_node2->count;
		
		while (iter1 < count1  && iter2 < count2) {
			key1	= keys1[iter1];
			key2	= keys2[iter2];

			next_key1 = iter1 + 1 < count1 ? keys1[iter1 + 1]: max1;
			next_key2 = iter2 + 1 < count2 ? keys2[iter2 + 1]: max2;
			which_iter = (next_key2 < next_key1);//1 means next_iter should be of key1 series.

			if (key1 == key2) { //case 0
				prev_iter = 0;
				common += intersection_inner_inner(new_level, inner_node1->values[iter1], 
												   inner_node2->values[iter2], next_key1, next_key2,
												   which_iter, prev_iter, done);
				
                if (which_iter) { // 1 means LHS
					iter1 += ((next_key1 <= next_key2) || done);
					iter2 += (next_key2 <= next_key1);	
				} else {
					iter2 += ((next_key2 <= next_key2) || done);
					iter1 += (next_key1 <= next_key2);
				}

			} else if (key1 < key2 && next_key1 > key2) {//case 1
				common += intersection_inner_inner(new_level, inner_node1->values[iter1], 
												   inner_node2->values[iter2], next_key1, next_key2,
												   which_iter, prev_iter, done);
				if (which_iter) { // 1 means LHS
					iter1 += ((next_key1 <= next_key2) || done);
					iter2 += (next_key2 <= next_key1);	
				} else {
					iter2 += ((next_key2 <= next_key2) || done);
					iter1 += (next_key1 <= next_key2);
				}

			} else if (key2 < key1 && next_key2 > key1) {//case 2
				which_iter = (next_key1 < next_key2);//1 means next_iter should be of key2 series.
				common += intersection_inner_inner(new_level, inner_node2->values[iter2], 
												   inner_node1->values[iter1], next_key1, next_key2,
												    which_iter, prev_iter, done);
				if (which_iter) { // 1 means LHS
					iter2 += ((next_key2 <= next_key2) || done);
					iter1 += (next_key1 <= next_key2);
				} else {
					iter1 += ((next_key1 <= next_key2) || done);
					iter2 += (next_key2 <= next_key1);	
				}
			} else {
				iter1 += (next_key1 <= next_key2);
				iter2 += (next_key2 <= next_key1);	
			}
			
		}
	} else { // leaf handling
		kleaf_node_t* leaf_node1 = (kleaf_node_t*)node1;
		kleaf_node_t* leaf_node2 = (kleaf_node_t*)node2;
		keys1	= leaf_node1->keys;
		keys2	= leaf_node2->keys;
		count1  = leaf_node1->count;
		count2	= leaf_node2->count;
		
		while (iter1 < count1 && iter2 < count2) {
			key1 = keys1[iter1];
			key2 = keys2[iter2];
			common += (key1 == key2);
			iter1 += (key1 <= key2);
			iter2 += (key2 <= key1);
		}
	}

	if (which_iter == 1) { 
		done = (iter1 == count1);
		past_iter = iter1;
	} else {
		done = (iter2 == count2);
		past_iter = iter2;
	}

	if (done) past_iter = 0;

	return common;
}

//inner_node1 has smaller depth
int equalize_inner(kinner_node_t* inner_node1, degree_t& iter1, kinner_node_t* inner_node2, key_t max1, key_t max2)
{
	int level1 = inner_node1->level;
	int level2 = inner_node2->level;
	int level = level2 - level1;
	int common = 0;
	
	
	if (level > 0) {
		key_t*		keys1	= inner_node1->keys;
		key_t*		keys2	= inner_node2->keys;
		degree_t	count1	= inner_node1->count;
		degree_t	count2	= inner_node2->count; 
		
		key_t		key1;
		key_t		key2;
		key_t		next_key1;
		key_t		next_key2;
		
		degree_t	iter2	= 0;

		degree_t	prev_iter = 0; //will apply to LHS iter
		degree_t	next_iter;	//will apply to LHS iter
		
		while (iter1 < count1 && iter2 < count2) {
			key1 = keys1[iter1];
			key2 = keys2[iter2];
			next_key1 = (iter1+1 < count1) ? keys1[iter1+1]: max1;
			next_key2 = (iter2+1 < count2) ? keys1[iter2+1]: max2;

			if (key1 == key2) { //case 0
				prev_iter = 0;
				common += equalize_inner(inner_node1, iter1, 
									   (kinner_node_t*)inner_node2->values[iter2],
									   max1, next_key2);

			} else if (key1 < key2 && next_key1 > key2) {//case 1
				common += equalize_inner(inner_node1, iter1, 
									   (kinner_node_t*)inner_node2->values[iter2], 
									   max1, next_key2);

			} else if (key2 < key1 && next_key2 > key1) {//case 2
				common += equalize_inner(inner_node1, iter1, 
									   (kinner_node_t*)inner_node2->values[iter2],
									   max1, next_key2);
			} else {
				iter1 += (next_key1 <= next_key2);
				iter2 += (next_key2 <= next_key1);	
			}
		}
	} else {
		int done = 0;
		return intersection_inner_inner(level1, inner_node1, 
										inner_node2, max1, max2,
										1, iter1, done);
	}
}

int kbtree_t::intersection22(kbtree_t* btree2)
{
	kinner_node_t* inner_node1 = btree.inner_node;
	kinner_node_t* inner_node2 = btree2->btree.inner_node;
	int level1 = inner_node1->level;
	int level2 = inner_node2->level;
	
	degree_t iter = 0; //will apply to LHS iter
	int done = 0;
	if (level1 == level2) {
		return intersection_inner_inner(inner_node1->level, inner_node1, 
									inner_node2, KEY_MAX, KEY_MAX,
									0, iter, done);
	} else if (level1 < level2) {
		return equalize_inner(inner_node1, iter, inner_node2, KEY_MAX, KEY_MAX);
	} else {
		return equalize_inner(inner_node2, iter, inner_node1, KEY_MAX, KEY_MAX);
	}
}
