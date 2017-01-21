#include "edges.h"
#include "stdlib.h"

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
kbtree_t::insert(key_t key)
{
	kinner_node_t* tmp_inner_node;
	if (degree < inplace_knode) {
		inplace_keys[degree] = key;
	} else if (degree < kleaf_keys) {
		btree.leaf_node->keys[degree - 1] = key;
	} else {
		tmp_inner_node = btree.inner_node;
		unsigned int i = 0;
		while (key < tmp_inner_node->keys[i] && i < tmp_inner_node->count) {

			++i;
		}
	}
	++degree;
	return 0;
}
