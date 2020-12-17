#pragma once
#include <iostream>
#include <vector>

using namespace std;
static const char* nodeTypeList[] = {
    "Program",                        //���ڵ�

    "FunctionDefinitions",            //�����������

    "FunctionDefinition",             //��������

    "Statements",                     //��������
    "Statement",                      //���

    "DeclarationStatement",           //�������
    "DeclarationRightStatement",    //���������ֵ
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
     "ConditionStatement",       //�������


    "PRINTLN", // println!("{}", id);

   "LogicalOrExpressionE",            //������ݹ�
   "LogicalAndExpressionE",
   "InclusiveOrExpressionE",
   "ExclusiveOrExpressionE",
   "AndExpressionE",
   "EqualityExpressionE",
   "RelationalExpressionE",
   "ShiftExpressionE",
   "AdditiveExpressionE",
   "MultiplicativeExpressionE",
};

enum class node_type
{
    Program,                        //���ڵ�

    FunctionDefinitions,            //�����������
         
    FunctionDefinition,             //��������

    Statements,                     //��������
    Statement,                      //���

    DeclarationStatement,           //�������
    DeclarationRightStatement,    //���������ֵ
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
    ConditionStatement,       //�������

    COMMENT, //ע��

    PRINTLN, // println!("{}", id);

    LogicalOrExpressionE,            //������ݹ�
    LogicalAndExpressionE,          
    InclusiveOrExpressionE,          
    ExclusiveOrExpressionE,          
    AndExpressionE,                  
    EqualityExpressionE,             
    RelationalExpressionE,       
    ShiftExpressionE,                
    AdditiveExpressionE,           
    MultiplicativeExpressionE,
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