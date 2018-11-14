//
// Created by qianb on 2018/11/14.
//

#include "objDetector.h"



typedef std::map<std::string, objDetector_factory::creator> creator_map;

static creator_map& get_registry(void)
{
    static creator_map * instance_ptr=new creator_map();

    return *instance_ptr;
}

void objDetector_factory::register_creator(const std::string& name, creator& create_func)
{
    creator_map& registry=get_registry();

    registry[name]=create_func;
}

std::vector<std::string> objDetector_factory::list(void)
{
    std::vector<std::string> ret;

    creator_map& registry=get_registry();

    creator_map::iterator it=registry.begin();

    while(it!=registry.end())
    {
        ret.push_back(it->first);
        it++;
    }

    return ret;
}


objDetector * objDetector_factory::create_detector(const std::string& name)
{

    creator_map& registry=get_registry();

    if(registry.find(name)== registry.end())
        return nullptr;

    creator func=registry[name];

    return func();
}
