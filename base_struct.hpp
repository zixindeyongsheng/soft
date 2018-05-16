//
//  base_struct.hpp
//  hotelapp
//
//  Created by wjh on 2018/5/16.
//  Copyright © 2018年 王竞晖. All rights reserved.
//

#ifndef base_struct_hpp
#define base_struct_hpp

#include "node.hpp"
enum speed {SLOW, MID, HIGH};
template <typename T>
class base_struct {
private:
    int  _size;
    //头、尾哨兵永远存在
    nodePos(T) header;//头哨兵
    nodePos(T) trailer;//尾哨兵
protected:
    virtual void init() = 0;//创建时初始化
    virtual int clear() = 0;//清除所有节点，返回清除后节点个数
    virtual void sort() = 0;//排序
public:
    //构造函数
    base_struct(){init();};
    base_struct(base_struct<T> const & L);//拷贝构造函数
    ~base_struct();
    //只读接口
    int size()const{return _size;};
    nodePos(T) first() const{return header->suc;};//返回首节点指针
    nodePos(T) last() const{return trailer->pre;};//返回尾节点指针
    virtual bool ordered()const = 0;//返回是否有序
    virtual nodePos(T) find(T const& e)const = 0;//查找相应内容的节点
    virtual nodePos(T) topN(int const N)const = 0;//返回前N个节点
    virtual nodePos(T) ranklist(speed rank)const = 0;//返回档次为rank的所有节点
    //可写接口
    virtual nodePos(T) insertAsFirst(T const& e) = 0;//将e当作首节点插入
    virtual nodePos(T) insertAsLast(T const& e) = 0;//将e当作尾节点插入
    virtual nodePos(T) insertAhead(T const& e, nodePos(T) index) = 0;//将e插在index之前
    virtual nodePos(T) insertBehind(T const& e, nodePos(T) index) = 0;//将e插在index之后
    virtual T remove(nodePos(T) p);//删除节点，返回其值
    
    
    
};

#endif /* base_struct_hpp */
