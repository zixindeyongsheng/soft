//
//  node.hpp
//  hotelapp
//
//  Created by wjh on 2018/5/16.
//  Copyright © 2018年 王竞晖. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

typedef int Rank;
#define nodePos(T) node<T>*

template <typename T>
class node {
    T data;
    nodePos(T) pre;
    nodePos(T) suc;
    node(){
        throw "not defined error\n";
    };
    node(T e, nodePos(T) p = nullptr, nodePos(T) s = nullptr):data(e), pre(p), suc(s){
        throw "not defined error\n";
    };
    node(const node& n){
        throw "not defined error\n";
    };
    virtual nodePos(T) insertAsPre(T const &e) = 0;//在节点前插入
    virtual nodePos(T) insertAsSuc(T const &e) = 0;//在节点后插入
    
};

#endif /* node_hpp */
