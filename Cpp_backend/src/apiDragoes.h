#ifndef CPP_DRAGOES_H
#define CPP_DRAGOES_H

#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>

void getDragoes(const httplib::Request& req, httplib::Response& res);
void postDragoes(const httplib::Request& req, httplib::Response& res);
void getDragaoFromId(const httplib::Request& req, httplib::Response& res);

#endif