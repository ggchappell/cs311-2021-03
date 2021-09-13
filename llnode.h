// llnode.h
// Glenn G. Chappell
// 2021-09-13
//
// For CS 311 Fall 2021
// Header for struct LLNode
// Singly Linked List node
// There is no associated source file.

#ifndef FILE_LLNODE_H_INCLUDED
#define FILE_LLNODE_H_INCLUDED


// *********************************************************************
// struct LLNode - Struct definition
// *********************************************************************


// struct LLNode
// Singly Linked List node, with client-specified value type
// Invariants:
//     Either _next is nullptr, or _next points to an LLNode, allocated
//      with new, owned by *this.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
template <typename ValType>
struct LLNode {
    ValType   _data;  // Data for this node
    LLNode *  _next;  // Ptr to next node, or nullptr if none

    // The following simplify creation & destruction

    // 1- & 2-param ctor
    // _data is set to data (given). _next is set to next, if given, or
    // nullptr if not.
    // Pre:
    //     theNext, if passed, is either nullptr, or else it points to
    //      an LLNode allocated with new, with ownership transferred to
    //      *this.
    explicit LLNode(const ValType & data,
                    LLNode * next = nullptr)
        :_data(data),
         _next(next)
    {}

    // dctor
    // Does delete on _next.
    ~LLNode()
    { delete _next; }

    // No default ctor, no copy/move operations.
    LLNode() = delete;
    LLNode(const LLNode & other) = delete;
    LLNode & operator=(const LLNode & other) = delete;
    LLNode(LLNode && other) = delete;
    LLNode & operator=(LLNode && other) = delete;

};  // End struct LLNode


#endif  //#ifndef FILE_LLNODE_H_INCLUDED

