//
// Copyright (C) 2015-2017 Yahoo Japan Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <string>
#include <iostream>
#include <sstream>

#include "NGT/Index.h"
#include "Capi.h"

static bool operate_error_string_(const std::stringstream &ss, NGTError error){
  if(error != NULL){  
    try{
      std::string *error_str = static_cast<std::string*>(error);
      *error_str = ss.str();
    }catch(std::exception &err){
      std::cerr << ss.str() << " > " << err.what() << std::endl;
      return false;
    }
  }else{
    std::cerr << ss.str() << std::endl;
  }
  return true;
}

NGTIndex ngt_open_index(const char *index_path, NGTError error) {
  try{
    std::string index_path_str(index_path);
    return static_cast<NGTIndex>(new NGT::Index(index_path_str));
  }catch(std::exception &err){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);
    return NULL;
  }
}
    
NGTIndex ngt_create_graph_and_tree(const char *database, NGTProperty prop, NGTError error) {
  NGT::Index *index = NULL;
  try{
    std::string database_str(database);
    NGT::Property prop_i = *(static_cast<NGT::Property*>(prop));    
    
    index = new NGT::Index();
    index->createGraphAndTree(database_str, prop_i);
    return static_cast<NGTIndex>(index);
  }catch(std::exception &err){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);    
    delete index;
    return NULL;
  }
}

NGTProperty ngt_create_property(NGTError error) {
  try{
    return static_cast<NGTProperty>(new NGT::Property());
  }catch(std::exception &err){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);        
    return NULL;
  }
}

int ngt_save_index(const NGTIndex index, const char *database, NGTError error) {
  try{
    std::string database_str(database);
    (static_cast<NGT::Index*>(index))->saveIndex(database_str);
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);    
    return 0;
  }
  return 1;
}

int ngt_get_property(NGTIndex index, NGTProperty prop, NGTError error) {
  if(index == NULL || prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: index = " << index << " prop = " << prop;
    operate_error_string_(ss, error);        
    return 0;
  }
  
  try{
    (static_cast<NGT::Index*>(index))->getProperty(*(static_cast<NGT::Property*>(prop)));
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);
    return 0;
  }
  return 1;
}

int ngt_get_property_dimension(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);    
    return -1;
  }
  return (*static_cast<NGT::Property*>(prop)).dimension;      
}

int ngt_set_property_dimension(NGTProperty prop, int value, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;            
    operate_error_string_(ss, error);
    return 0;
  }
  (*static_cast<NGT::Property*>(prop)).dimension = value;
  return 1;
}

int ngt_set_property_edge_size_for_creation(NGTProperty prop, int value, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);    
    return 0;
  }
  (*static_cast<NGT::Property*>(prop)).edgeSizeForCreation = value;
  return 1;
}

int ngt_set_property_edge_size_for_search(NGTProperty prop, int value, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;            
    operate_error_string_(ss, error);        
    return 0;
  }
  (*static_cast<NGT::Property*>(prop)).edgeSizeForSearch = value;
  return 1;
}

int ngt_get_property_object_type(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);              
    return -1;
  }
  return (*static_cast<NGT::Property*>(prop)).objectType;
}

int ngt_is_property_object_type_float(int object_type) {
    return (object_type == NGT::Index::Property::ObjectType::Float);
}

int ngt_is_property_object_type_integer(int object_type) {
    return (object_type == NGT::Index::Property::ObjectType::Uint8);
}

int ngt_set_property_object_type_float(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);                    
    return 0;
  }
  
  (*static_cast<NGT::Property*>(prop)).objectType = NGT::Index::Property::ObjectType::Float;
  return 1;
}

int ngt_set_property_object_type_integer(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);
    return 0;
  }
  
  (*static_cast<NGT::Property*>(prop)).objectType = NGT::Index::Property::ObjectType::Uint8;
  return 1;
}

int ngt_set_property_distance_type_l1(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);      
    return 0;
  }
  
  (*static_cast<NGT::Property*>(prop)).distanceType = NGT::Index::Property::DistanceType::DistanceTypeL1;
  return 1;
}

int ngt_set_property_distance_type_l2(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);            
    return 0;
  }
  
  (*static_cast<NGT::Property*>(prop)).distanceType = NGT::Index::Property::DistanceType::DistanceTypeL2;
  return 1;
}

int ngt_set_property_distance_type_angle(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);                  
    return 0;
  }
  
  (*static_cast<NGT::Property*>(prop)).distanceType = NGT::Index::Property::DistanceType::DistanceTypeAngle;
  return 1;
}

int ngt_set_property_distance_type_hamming(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);                        
    return 0;
  }
  
  (*static_cast<NGT::Property*>(prop)).distanceType = NGT::Index::Property::DistanceType::DistanceTypeHamming;
  return 1;
}

NGTObjectDistances ngt_create_empty_results(NGTError error) {
  try{
    return static_cast<NGTObjectDistances>(new NGT::ObjectDistances());
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);                              
    return NULL;
  }
}

int ngt_search_index(NGTIndex index, double *query, int query_dim, int size, float epsilon, NGTObjectDistances results, NGTError error) {
  if(index == NULL || query == NULL || results == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: index = " << index << " query = " << query << " results = " << results;
    operate_error_string_(ss, error);
    return 0;
  }
  
  NGT::Index* pindex = static_cast<NGT::Index*>(index);    
  NGT::Object *ngtquery = NULL;
  const float radius = FLT_MAX;

  try{	  
    std::vector<double> vquery(&query[0], &query[query_dim]);
    ngtquery = pindex->allocateObject(vquery);
    // set search prameters.
    NGT::SearchContainer sc(*ngtquery);      // search parametera container.
    
    sc.setResults(static_cast<NGT::ObjectDistances*>(results));          // set the result set.
    sc.setSize(size);             // the number of resultant objects.
    sc.setRadius(radius);         // search radius.
    sc.setEpsilon(epsilon);           // set exploration coefficient.
    
    pindex->search(sc);
    
    // delete the query object.
    pindex->deleteObject(ngtquery);
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);      
    if(ngtquery != NULL){
      pindex->deleteObject(ngtquery);
    }
    return 0;
  }
  return 1;
}

int ngt_get_size(NGTObjectDistances results, NGTError error) {
  if(results == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: results = " << results;
    operate_error_string_(ss, error);            
    return -1;
  }
  
  return (static_cast<NGT::ObjectDistances*>(results))->size();
}

NGTObjectDistance ngt_get_result(const NGTObjectDistances results, const int i, NGTError error) {
  try{
    NGT::ObjectDistances objects = *(static_cast<NGT::ObjectDistances*>(results));
    NGTObjectDistance ret_val = {objects[i].id, objects[i].distance};
    return ret_val;
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);
    
    NGTObjectDistance err_val = {0};
    return err_val;
  }
}

ObjectID ngt_insert_index(NGTIndex index, double *obj, int obj_dim, NGTError error) {
  try{
    NGT::Index* pindex = static_cast<NGT::Index*>(index);
    std::vector<double> vobj(&obj[0], &obj[obj_dim]);
    return pindex->insert(vobj);    
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);      
    return 0;
  }
}

int ngt_create_index(NGTIndex index, int pool_size, NGTError error) {
  if(index == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: idnex = " << index;
    operate_error_string_(ss, error);            
    return 0;
  }
  
  try{
    (static_cast<NGT::Index*>(index))->createIndex(pool_size);
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);                  
    return 0;
  }
  return 1;
}

int ngt_remove_index(NGTIndex index, ObjectID id, NGTError error) {
  if(index == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: idnex = " << index;
    operate_error_string_(ss, error);                        
    return 0;
  }
  
  try{
    (static_cast<NGT::Index*>(index))->remove(id);
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);                              
    return 0;
  }
  return 1;
}

NGTObjectSpace ngt_get_object_space(NGTIndex index, NGTError error) {
  if(index == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: idnex = " << index;
    operate_error_string_(ss, error);                                    
    return NULL;
  }
  
  try{
    return static_cast<NGTObjectSpace>(&(static_cast<NGT::Index*>(index))->getObjectSpace());
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);
    return NULL;
  }
}

float* ngt_get_object_as_float(NGTObjectSpace object_space, int id, NGTError error) {
  if(object_space == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: object_space = " << object_space;
    operate_error_string_(ss, error);      
    return NULL;
  }
  
  try{
    return static_cast<float*>((static_cast<NGT::ObjectSpace*>(object_space))->getObject(id));    
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);
    return NULL;
  }
}

uint8_t* ngt_get_object_as_integer(NGTObjectSpace object_space, int id, NGTError error) {
  if(object_space == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: object_space = " << object_space;
    operate_error_string_(ss, error);      
    return NULL;
  }

  try{
    return static_cast<uint8_t*>((static_cast<NGT::ObjectSpace*>(object_space))->getObject(id));;    
  }catch(std::exception &err) {
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    operate_error_string_(ss, error);
    return NULL;
  }
}

void ngt_destroy_results(NGTObjectDistances results) {
    if(results == NULL) return;
    delete(static_cast<NGT::ObjectDistances*>(results));
}

void ngt_destroy_property(NGTProperty prop) {
    if(prop == NULL) return;  
    delete(static_cast<NGT::Property*>(prop));
}

void ngt_close_index(NGTIndex index) {
    if(index == NULL) return;
    (static_cast<NGT::Index*>(index))->close();
    delete(static_cast<NGT::Index*>(index));
}

int ngt_get_property_edge_size_for_creation(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);      
    return -1;
  }
  return (*static_cast<NGT::Property*>(prop)).edgeSizeForCreation;
}

int ngt_get_property_edge_size_for_search(NGTProperty prop, NGTError error) {
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);            
    return -1;
  }
  return (*static_cast<NGT::Property*>(prop)).edgeSizeForSearch;
}

int ngt_get_property_distance_type(NGTProperty prop, NGTError error){
  if(prop == NULL){
    std::stringstream ss;
    ss << "Capi : " << __FUNCTION__ << "() : parametor error: prop = " << prop;
    operate_error_string_(ss, error);                  
    return -1;
  }
  return (*static_cast<NGT::Property*>(prop)).distanceType; 
}

NGTError ngt_create_error_object()
{
  try{
    std::string *error_str = new std::string();
    return static_cast<NGTError>(error_str);
  }catch(std::exception &err){
    std::cerr << "Capi : " << __FUNCTION__ << "() : Error: " << err.what();
    return NULL;
  }    
}

const char *ngt_get_error_string(const NGTError error)
{
  std::string *error_str = static_cast<std::string*>(error);
  return error_str->c_str();
}

void ngt_clear_error_string(NGTError error)
{
  std::string *error_str = static_cast<std::string*>(error);
  *error_str = "";
}

void ngt_destroy_error_object(NGTError error)
{
  std::string *error_str = static_cast<std::string*>(error);
  delete error_str;
}
