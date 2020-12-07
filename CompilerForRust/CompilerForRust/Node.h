#pragma once
#include <iostream>
#include <vector>

using namespace std;
static const char* nodeTypeList[] = {
    "Program",                        //���ڵ�

    "FunctionDefinitions",            //�����������
    "Main",

    "FunctionDefinition",             //��������

    "Statements",                     //��������
    "Statement",                      //���

    "DeclarationStatement",           //�������
    "ExpressionStatement",
    "AssignmentExpression",
    "TypeExpression",

    "VariableDefinition",             //�ɱ����
    "DataType",
    "LiteralExpression",

    "Variable",

    "BlockExpression",
    "LogicalOrExpression",
    "GroupedExpression",
    "FunctionCall",
    "ContinueExpression",
    "BreakExpression",
    "IfExpression",
    "ReturnExpression",

    "Identifier",                     //��ʶ��

    "CHAR_STR_LITERAL",               //' [A-Za-z] ' | e
    "INTEGER_LITERAL",                //[0-9]*
    "FLOAT_LITERAL",                  //[0-9]*.[0-9]*
    "BOOLEAN_LITERAL",                //true | false

    "CycleExpression",                //ѭ��

    "WhileExpression",
    "ForExpression",
    "LoopExpression",

    "FunctionIdentifier",             //������
    "ParameterList",
    "CallParameterList",

    "AssignmentOperator",             // [*,/,-,+,<<,>>,%,&,^,|]?=
    "LogicalAndExpression",           // &&
    "InclusiveOrExpression",          // |
    "ExclusiveOrExpression",          // ^
    "AndExpression",                  // &
    "EqualityExpression",             // == | !=
    "RelationalExpression",           // [<,>]=?
    "ShiftExpression",                // << | >>
    "AdditiveExpression",             // + | -
    "MultiplicativeExpression",       // * | / | %
    "NotExpression",                  // !
    "PrimaryExpression",              // (?)?

    "PRINTLN", // println!("{}", id);
};

enum class node_type
{
    Program,                        //���ڵ�

    FunctionDefinitions,            //�����������
    Main,
         
    FunctionDefinition,             //��������

    Statements,                     //��������
    Statement,                      //���

    DeclarationStatement,           //�������
    ExpressionStatement,
    AssignmentExpression,
    TypeExpression,

    VariableDefinition,             //�ɱ����
    DataType,
    LiteralExpression,

    Variable,

    BlockExpression,
    LogicalOrExpression,
    GroupedExpression,
    FunctionCall,
    ContinueExpression,
    BreakExpression,
    IfExpression,
    ReturnExpression,

    Identifier,                     //��ʶ��

    CHAR_STR_LITERAL,               //' [A-Za-z] ' | e
    INTEGER_LITERAL,                //[0-9]*
    FLOAT_LITERAL,                  //[0-9]*.[0-9]*
    BOOLEAN_LITERAL,                //true | false

    CycleExpression,                //ѭ��

    WhileExpression,
    ForExpression,
    LoopExpression,

    FunctionIdentifier,             //������
    ParameterList,
    CallParameterList,

    AssignmentOperator,             // [*,/,-,+,<<,>>,%,&,^,|]?=
    LogicalAndExpression,           // &&
    InclusiveOrExpression,          // |
    ExclusiveOrExpression,          // ^
    AndExpression,                  // &
    EqualityExpression,             // == | !=
    RelationalExpression,           // [<,>]=?
    ShiftExpression,                // << | >>
    AdditiveExpression,             // + | -
    MultiplicativeExpression,       // * | / | %
    NotExpression,                  // !
    PrimaryExpression,              // (?)?

    PRINTLN, // println!("{}", id);
};
class Node
{
public:
    string value;
    node_type type;
    vector<unique_ptr<Node>> childNodes;

public:
    Node(const string value, node_type type);
    Node(const string value, node_type type, vector<unique_ptr<Node>> childNodes);
    Node();
    ~Node();
    void addChildNode(unique_ptr<Node> childNode);
};