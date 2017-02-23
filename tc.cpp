

//It will not do a deep copy, memory will be used.
void
tc_t::init_from_csr2(csr_t* data, int sorted)
{
	vertex_t		vert_count = data->vert_count;
	adj_list_t*		adj_list = (adj_list_t*)malloc(sizeof(adj_list_t)*vert_count);
	
	udata.vert_count	= vert_count;
	udata.adj_list		= adj_list;

	#pragma omp parallel
	{
	vertex_t degree = 0;
	int leaf_count = 0;
	vertex_t* l_adj_list = 0;
	int level1_count = 0;
	#pragma omp for
	for (vertex_t i = 0; i < vert_count; ++i) {
		degree = data->beg_pos[i + 1] - data->beg_pos[i];
		l_adj_list = data->adj_list + data->beg_pos[i];
		adj_list[i].degree = degree;
		
		if (!sorted) sort(l_adj_list, l_adj_list + degree);
		
		if (degree <= kinline_keys) {
			for (degree_t j = 0; j < degree; ++j) {
				adj_list[i].btree.inplace_keys[j] = l_adj_list[j];
			}
		} else if (degree <= kleaf_keys) {
			adj_list[i].btree.leaf_node = (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
			adj_list[i].btree.leaf_node->count = degree;
			memcpy(adj_list[i].btree.leaf_node->keys, 
				   l_adj_list, 
				   degree*sizeof(vertex_t));
			
		} else {
			leaf_count = degree/kleaf_keys + (0 != degree % kleaf_keys);
			level1_count = leaf_count/kinner_values + (0 != leaf_count % kinner_values);
			
			kinner_node_t* inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			udata.adj_list[i].btree.inner_node = inner_node;
			
			degree_t remaining = degree;
			int remaining_leaf = leaf_count;
			degree_t count = kleaf_keys;
			int inner_count = kinner_keys;
			kinner_node_t* prev = 0;
			kleaf_node_t* leaf_node = 0;
			
			for (int j = 0; j < level1_count; ++j) {
				inner_count = min(kinner_keys, remaining_leaf);
				remaining_leaf -= inner_count;
				inner_node->count = inner_count;
				inner_node->level = 1;
			
				for (int k = 0; k < inner_count; ++k) {
				
					leaf_node = (kleaf_node_t*)malloc(sizeof(kleaf_node_t));
					count = min(kleaf_keys, remaining);
					remaining -= count;
					
					leaf_node->count  = count;
					leaf_node->sorted = 1;
					
					memcpy(leaf_node->keys,
						   l_adj_list, count*sizeof(vertex_t));

					inner_node->values[k] = leaf_node;
					inner_node->keys[k] = leaf_node->keys[0];
					
					l_adj_list += count;
				}

				prev = inner_node;
				inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
				prev->next = inner_node;
			}

			//delete last allocation and the link
			free(inner_node);
			prev->next = 0;
		}

		//Make higher node
		degree_t level_count = level1_count;
		while (level_count > kinner_values) {
			degree_t remaining = level_count;
			level_count = level_count/kinner_values + (0 != level_count % kinner_values);
			kinner_node_t* tmp_inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
			kinner_node_t* inner_node	  = udata.adj_list[i].btree.inner_node;
			int			   level		  = inner_node->level + 1; 
			
			udata.adj_list[i].btree.inner_node = tmp_inner_node;
			
			kinner_node_t* prev = 0;
			degree_t inner_count = kinner_keys;	
			
			for (int j = 0; j < level_count; ++j) {
				inner_count = min(kinner_keys, remaining);
				remaining -= inner_count;

				tmp_inner_node->count = inner_count;
				tmp_inner_node->level = level;
			
				for (int k = 0; k < inner_count; ++k) {
					tmp_inner_node->values[k] = inner_node;
					tmp_inner_node->keys[k] = inner_node->keys[0];
					inner_node = inner_node->next;	
				}

				prev = tmp_inner_node;
				tmp_inner_node = (kinner_node_t*)malloc(sizeof(kinner_node_t));
				prev->next = tmp_inner_node;
			}

			//delete last allocation and the link
			free(tmp_inner_node);
			prev->next = 0;
		}
	}
	}
}

index_t tc_t::tc()
{
	vertex_t vert_count = udata.vert_count;
	adj_list_t* adj_list   = udata.adj_list;
	
	vertex_t v1, v2;
	degree_t degree;
	kinner_node_t*	inner_node = 0;
	vertex_t*		nebrs = 0;
	int				count = 0;
	index_t			tc_count = 0;

	for(vertex_t v = 0; v < vert_count; ++v) {
		degree = udata.adj_list[v].degree;
		if (degree <= kinline_keys) {//Path 1:
			nebrs = adj_list[v].btree.inplace_keys;
			count = degree;
			for (int j = 0; j < count; ++j) {
				v1 = v;
				v2 = nebrs[j];
				tc_count += intersection(v1, v2);
			}

		} else if (degree <= kleaf_keys) {//Path 2;
			nebrs = adj_list[v].btree.leaf_node->keys;
			count = adj_list[v].btree.leaf_node->count;
			for (int j = 0; j < count; ++j) {
				v1 = v;
				v2 = nebrs[j];
				tc_count += intersection(v1, v2);
			}

		} else {//Path 3:
			inner_node = udata.adj_list[v].btree.inner_node;
			while (inner_node) {
				for (int i = 0; i < inner_node->count; ++i) {
					nebrs = ((kleaf_node_t*)inner_node->values[i])->keys;
					count = ((kleaf_node_t*)inner_node->values[i])->count;
					for (int j = 0; j < count; ++j) {
						v1 = v;
						v2 = nebrs[j];
						tc_count += intersection(v1, v2);

					}
				}
				inner_node = inner_node->next;
			}
		}
	}
	return tc_count;
}

index_t tc_t::intersection(vertex_t v1, vertex_t v2)
{
	return 1;
}
