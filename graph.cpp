#include <pthread.h>

#include "all.h"

index_t residue = 0;

map<string, get_graph_instance>  graph_instance;
map<string, get_encoder_instance>  encoder_instance;

snapid_t graph::get_snapid() {
    if (snapshot) return snapshot->snap_id;
    else   return 0;
}

void graph::incr_snapid(index_t snap_marker, index_t durable_marker /* = 0 */) 
{
    snapshot_t* next = new snapshot_t;
    if (snapshot) {
        next->snap_id = snapshot->snap_id + 1;

        if (durable_marker == 0) {
            next->durable_marker = snapshot->durable_marker;
        } else {
            next->durable_marker = durable_marker;
        }
    } else {
        next->snap_id = 1;
        next->durable_marker = 0;
    }

    next->marker = snap_marker;
    next->next = snapshot;
    snapshot = next;
    

    disk_snapshot_t* disk_snapshot = (disk_snapshot_t*)malloc(sizeof(disk_snapshot_t));
    disk_snapshot->snap_id= snapshot->snap_id;
    disk_snapshot->marker = snapshot->marker;
    disk_snapshot->durable_marker = snapshot->durable_marker;
    fwrite(disk_snapshot, sizeof(disk_snapshot_t), 1, snap_f);
}

graph::graph()
{
    cf_info  = 0;
    cf_count = 0;
    p_info   = 0;
    p_count  = 0;
    vert_count = 0;
    
    snapshot = 0;
    snap_f = 0;

    pthread_mutex_init(&snap_mutex, 0);
    pthread_cond_init(&snap_condition, 0);
    
    pthread_mutex_init(&w_mutex, 0);
    pthread_cond_init(&w_condition, 0);
    
    register_instances();
}
    
void graph::register_instances()
{
    graph_instance.insert(pair<string,get_graph_instance>("typekv_t", typekv_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("labelkv_t", labelkv_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("stringkv_t", stringkv_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("ugraph_t", ugraph_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("dgraph_t", dgraph_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("one2one_t", one2one_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("one2many_t", one2many_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("many2one_t", many2one_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("p_ugraph_t", p_ugraph_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("p_dgraph_t", p_dgraph_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("p_one2one_t", p_one2one_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("p_one2many_t", p_one2many_t::create_instance));
    graph_instance.insert(pair<string,get_graph_instance>("p_many2one_t", p_many2one_t::create_instance));
   
#ifdef B64 
    encoder_instance.insert(pair<string,get_encoder_instance>("time_encoder_t", time_encoder_t::create_instance));
    encoder_instance.insert(pair<string,get_encoder_instance>("int64_encoder_t", int64_encoder_t::create_instance));
    encoder_instance.insert(pair<string,get_encoder_instance>("double_encoder_t", double_encoder_t::create_instance));
    encoder_instance.insert(pair<string,get_encoder_instance>("embedstr_encoder_t", embedstr_encoder_t::create_instance));
#endif

}

void graph::create_schema(propid_t count, const string& conf_file)
{
    cf_info  = new cfinfo_t*[count];
    p_info   = new pinfo_t[count];

    pinfo_t* p_info1 = p_info;
    
    cfinfo_t*   info      = 0;
    prop_encoder_t* encoder = 0;
    const char* longname  = 0;
    const char* shortname = 0;
    const char* p_name = 0;

    //read the conf file
    char* line = 0;
    size_t len = 0;
    ssize_t read;
    char* saveptr;
    char* token;
    int value = -1;
    char splchar = '%'; 
    string delim = " ";
    string schema = "%%schema%%";
    map<string, get_graph_instance>::iterator iter1;
    map<string, get_encoder_instance>::iterator iter2;


    FILE* fp = fopen(conf_file.c_str(), "r");
    if (NULL == fp) assert(0);

    while((read = getline(&line, &len, fp)) != -1) {
        if (line[read - 1] == '\n') line[read - 1] = 0;
        if (line[0] == splchar && line[1] == splchar) {
            if (0 == strncmp(line, schema.c_str(), 10)) value = 0;
            else assert(0);
        
        } else {
            if (0 == value) {
                if( 0 == (token = strtok_r(line, delim.c_str(), &saveptr))) {
                    assert(0);
                }
                longname = token;
                shortname = token;
                g->add_property(longname);
                p_info1->populate_property(longname, shortname);
                
                if( 0 == (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                    assert(0);
                }
                iter1 = graph_instance.find(token);
                if (graph_instance.end() == iter1) {
                    assert(0);
                }
                info = iter1->second();

                if( 0 != (token = strtok_r(NULL, delim.c_str(), &saveptr))) {
                    p_name = token;
                    token = strtok_r(NULL, delim.c_str(), &saveptr);
                    iter2 = encoder_instance.find(token);
                    if (encoder_instance.end() == iter2) {
                        assert(0);
                    }
                    encoder = iter2->second();
                    info->add_edge_property(p_name, encoder);
                }
                g->add_columnfamily(info);
                info->create_columns();
                info->add_column(p_info1);
                ++p_info1;
            }
        }
    }
}

sid_t graph::get_type_scount(tid_t type/*=0*/)
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(cf_info[0]);
    return typekv->get_type_scount(type);
}

tid_t graph::get_total_types()
{
    typekv_t* typekv = dynamic_cast<typekv_t*>(cf_info[0]);
    return typekv->get_total_types();
}

sid_t graph::type_update(const string& src, const string& dst/*="gtype"*/)
{
    return get_typekv()->type_update(src, dst);
}

void graph::type_done()
{
    typekv = (typekv_t*) cf_info[0];
    typekv->make_graph_baseline();
}

void graph::type_store(const string& odir)
{
    typekv = (typekv_t*) cf_info[0];
    typekv->store_graph_baseline();
}

propid_t graph::get_cfid(propid_t pid)
{
    return p_info[pid].cf_id;
}

propid_t graph::get_cfid(const char* predicate)
{
    propid_t pid = get_pid(predicate);
    return p_info[pid].cf_id;
}

tid_t graph::get_tid(const char* type)
{
    typekv_t* typekv = get_typekv();
	univ_t univ;
   	typekv->get_encoded_value(type, &univ);
	return univ.value_tid;
}

propid_t graph::get_pid(const char* predicate)
{
    map<string, propid_t>::iterator str2pid_iter = str2pid.find(predicate);
    if (str2pid_iter == str2pid.end()) {
        return INVALID_PID;
    }
    return str2pid_iter->second;
}

sid_t graph::get_sid(const char* src)
{
    return get_typekv()->get_sid(src);
}

status_t graph::add_property(const char* longname)
{
    map<string, propid_t>::iterator iter;
    iter = str2pid.find(longname);
    if (str2pid.end() == iter) {
        str2pid[longname] = p_count;
        p_count++;
        return eOK;
    }
    //XXX
    return eOK;
}
    
status_t graph::batch_update(const string& src, const string& dst, const string& predicate)
{
    map<string, propid_t>::iterator str2pid_iter;
    str2pid_iter = str2pid.find(predicate);
    if (str2pid_iter == g->str2pid.end()) {
        assert(0);
    }
    propid_t pid = str2pid_iter->second;
    propid_t cf_id = g->get_cfid(pid);
    if (pid != 0) { //non-type
      return  cf_info[cf_id]->batch_update(src, dst, pid);
    //} else { //Is already handled above
    }
    return eOK;
}
    
status_t graph::batch_update(const string& src, const string& dst, propid_t pid, 
                          propid_t count, prop_pair_t* prop_pair)
{
    propid_t cf_id = g->get_cfid(pid);
    if (pid != 0) { //non-type
      return  cf_info[cf_id]->batch_update(src, dst, pid, count, prop_pair);
    //} else { //Is already handled above
    }
    return eOK;
}

void graph::prep_graph_baseline()
{
    //swap 
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->prep_graph_baseline();
    }
}

void graph::swap_log_buffer()
{
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->swap_log_buffer();
    }
}

void graph::calc_degree()
{
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->calc_degree();
    }
}

void graph::make_graph_baseline()
{
    //make graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->make_graph_baseline();
    }
}

void graph::create_snapthread()
{
    if (0 != pthread_create(&snap_thread, 0, graph::snap_func , g)) {
        assert(0);
    }
}

void* graph::snap_func(void* arg)
{
    graph* g_ptr = (graph*)(arg);
    
    do {
        pthread_mutex_lock(&g_ptr->snap_mutex);
        pthread_cond_wait(&g_ptr->snap_condition, &g_ptr->snap_mutex);
        pthread_mutex_unlock(&g_ptr->snap_mutex);
        g_ptr->create_snapshot();
    } while(1);

    return 0;
}

void graph::create_snapshot()
{
    int work_done = 0;
    index_t snap_marker = 0;
    //index_t last_durable_marker = 0;
    do {
        work_done = 0;
        for (int i = 1; i < cf_count; i++) {
            if (eOK == cf_info[i]->move_marker(snap_marker)) {
                cf_info[i]->make_graph_baseline();
                cf_info[i]->update_marker();
                ++work_done;
			}
        }
        /*
        if (snap_marker - last_durable_marker >= (1L << 29) ) { //4 GB memory
            cf_info[1]->store_graph_baseline();
            last_durable_marker = snap_marker;
        }*/

        if (work_done != 0 ) { 
            incr_snapid(snap_marker, 0);
            //cf_info[1]->update_marker();
        } else {
            break;
        } 
    } while(true);
}

void graph::store_graph_baseline(bool clean)
{
    //Store graph
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->store_graph_baseline(clean);
    }
}

// Being called for write only,
// For loading, call read graph baseline
void graph::file_open(bool trunc)
{
    snap_f = fopen(snapfile.c_str(), "wb");//write + binary
    assert(snap_f != 0);
    
    for (int i = 0; i < cf_count; i++) {
        cf_info[i]->file_open(odirname, trunc);
    }
}

void graph::read_graph_baseline()
{
    read_snapshot();
    
    cf_info[0]->file_open(odirname, false);
    //typekv->prep_str2sid(str2vid);
    cf_info[0]->read_graph_baseline();
    
    for (int i = 1; i < cf_count; i++) {
        cf_info[i]->prep_graph_baseline();
        cf_info[i]->file_open(odirname, false);
        cf_info[i]->read_graph_baseline();
    }
    typekv = (typekv_t*) cf_info[0];
}

void graph::read_snapshot()
{
    snap_f = fopen(snapfile.c_str(), "r+b");
    assert(snap_f != 0);

    off_t size = fsize(snapfile.c_str());
    if (size == -1L) {
        assert(0);
    }
    
    snapid_t count = (size/sizeof(disk_snapshot_t));
    disk_snapshot_t* disk_snapshot = (disk_snapshot_t*)calloc(count, sizeof(disk_snapshot_t));
    fread(disk_snapshot, sizeof(disk_snapshot_t), count, snap_f);
    
    snapshot_t* next = 0;
    for (snapid_t i = 0; i < count; ++i) {
        next = new snapshot_t;
        next->snap_id = disk_snapshot[i].snap_id;
        next->marker = disk_snapshot[i].marker;
        next->durable_marker = disk_snapshot[i].durable_marker;
        next->next = snapshot;
        snapshot = next;
    }
}

/////////////////////////////////////////
void pinfo_t::populate_property(const char* longname, const char* property_name)
{
    p_name  = gstrdup(property_name);
    p_longname = gstrdup(longname);
    cf_id = 0;//will be corrected later
}

void graph::add_columnfamily(cfinfo_t* cf) 
{
    cf_info[cf_count] = cf;
    cf->cf_id = cf_count;
    cf_count++;
}


void graph::create_wthread()
{
    if (0 != pthread_create(&w_thread, 0, graph::w_func , g)) {
        assert(0);
    }
}

//void* graph::w_func(void* arg)
//{
//    cout << "enterting w_func" << endl; 
//    graph* g_ptr = (graph*)(arg);
//    
//    do {
//        pthread_mutex_lock(&g_ptr->w_mutex);
//        pthread_cond_wait(&g_ptr->w_condition, &g_ptr->w_mutex);
//        pthread_mutex_unlock(&g_ptr->w_mutex);
//        g_ptr->write_edgelog();
//        cout << "Writing w_thd" << endl;
//    } while(1);
//
//    return 0;
//}

void* graph::w_func(void* arg)
{
    cout << "enterting w_func" << endl; 
    graph* g_ptr = (graph*)(arg);
    
    do {
        g_ptr->write_edgelog();
        //cout << "Writing w_thd" << endl;
        usleep(10);
    } while(1);

    return 0;
}

void graph::write_edgelog()
{
    index_t work_done = 0;
    do {
        work_done = 0;
        for (int i = 1; i < cf_count; i++) {
            if (eOK == cf_info[i]->write_edgelog()) {
                ++work_done;
			}
            if (0 == work_done) break;
        }
    } while(true);
}
