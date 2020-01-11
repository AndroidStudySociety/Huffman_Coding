//
// Created by Jesson on 2020/1/9.
//

#ifndef CPLUSPLUS_HUFFMAN_H
#define CPLUSPLUS_HUFFMAN_H
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
//哈夫曼编码的结点类
struct HuffmanNode {
    int weight; // 权重，出现的次数或者频率
    char ch; // 存储符号
    string code; // 存储该符号对应的编码
    int leftChild, rightChild, parent; // 左、右孩子，父结点
};

class huffman {
public:
    huffman(string str); // 构造函数
    ~huffman(); // 析构函数
    void getMin(int &first, int &second, int parent); // 选取两个较小的元素
    void Merge(int first, int second, int parent); // 合并
    void Encode(); // 编码:利用哈夫曼编码原理对数据进行加密
    void Decode(string str); // 解码
private:
    HuffmanNode *HuffmanTree; // 数组
    int leafSize;//统计不同字符的个数
};


#endif //CPLUSPLUS_HUFFMAN_H
