#include "Node.h"

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value*> NamedValues;

Node::Node(const string value, node_type type) 
{
	this->type = type;
	this->value = value;
	this->childNodes.clear();
}
Node::Node(const string value, node_type type, vector<unique_ptr<Node>> childNodes)
{

	this->value = value;
	this->type = type;
	this->childNodes = move(childNodes);
}
Node::Node() {
	childNodes.clear();

};
Node::~Node() { childNodes.clear(); };
void Node::addChildNode(unique_ptr<Node> childNode)
{
	this->childNodes.push_back(move(childNode));
}

Type* getType(string returnVal) {
	if (returnVal == "i16" || returnVal == "u16") {
		return Type::getInt16Ty(TheContext);
	}
	else if (returnVal == "f32") {
		return Type::getFloatTy(TheContext);
	}
	else if (returnVal == "bool") {
		return Type::getInt1Ty(TheContext);
	}
	else {
		return Type::getInt8Ty(TheContext);
	}
}

unique_ptr<Node> LogError(const char* Str) {
	fprintf(stderr, "Error:%s\n", Str);
	return nullptr;
}
Value* LogErrorV(const char* Str) {
	LogError(Str);
	return nullptr;
}
/*
��Stringת��Ϊhashֵ����switch case
*/
typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const* str)
{
	hash_t ret{ basis };

	while (*str) {
		ret ^= *str;
		ret *= prime;
		str++;
	}

	return ret;
}
constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
}


Value* Node::codegen() {
	switch (type)
	{
	case node_type::FLOAT_LITERAL:
	{
		double doubleVal = atof(value.c_str());
		return ConstantFP::get(Type::getFloatTy(TheContext), doubleVal);
		break;
	}
	case node_type::INTEGER_LITERAL:
	{
		int intVal = atoi(value.c_str());
		return ConstantInt::get(Type::getInt16Ty(TheContext), intVal);
		break;
	}
	case node_type::BOOLEAN_LITERAL:
	{
		int boolVal = value == "true" ? 1 : 0;
		return ConstantInt::get(Type::getInt1Ty(TheContext), boolVal);
		break;
	}	
	case node_type::CHAR_STR_LITERAL:
		return ConstantInt::get(Type::getInt8Ty(TheContext), value[1]);
		break;
	case node_type::Program:
	{
		Value* functionDefinitionsChild = childNodes[0]->codegen();
		return nullptr;
	}
	case node_type::FunctionDefinitions: {
		for (int i = 0; i < childNodes.size(); i++) {
			childNodes[i]->codegen();
		}
		return nullptr;
	}
	case node_type::FunctionDefinition: {
		int nameIdx= -1, returnIdx = -1, argsIdx = -1, bodyIdx = -1;
		string nameVal, returnVal;
		for (int i = 0; i < childNodes.size(); i++) {
			node_type type = childNodes[i]->type;
			string value = childNodes[i]->value;
			if (type == node_type::FunctionIdentifier)
			{
				nameVal = value; nameIdx = i;
			}
			else if (type == node_type::DataType) {
				returnIdx = i; returnVal = value;
			}
			else if (type == node_type::ParameterList) {
				argsIdx = i;
			}
			else if (type == node_type::BlockExpression) {
				bodyIdx = i;
			}
		}
		Function* TheFunction = TheModule->getFunction(nameVal);
		if (!TheFunction)return TheFunction;
		Type* returnType;
		vector<Type*>args;
		vector<string>argNames;
		FunctionType* TheFunctionType;

		//ȷ������ֵ
		if (returnIdx != -1) {
			returnType = getType(returnVal);
		}
		else {
			returnType = Type::getVoidTy(TheContext);
		}
		
		//ȷ�������б�
		for (int j = 0; j < childNodes[argsIdx]->childNodes.size(); j++) {
			node_type type = childNodes[argsIdx]->childNodes[j]->type;
			string value = childNodes[argsIdx]->childNodes[j]->value;
			if (type == node_type::DataType)
				args.push_back(getType(value));
			else if (type == node_type::Variable)
				argNames.push_back(value);
		}

		//ȷ������ԭ��
		TheFunctionType = FunctionType::get(returnType, args, false);

		//ȷ������
		TheFunction = Function::Create(TheFunctionType, Function::ExternalLinkage, nameVal, TheModule.get());

		//��������
		int k = 0;
		for (auto& Arg : TheFunction->args()) {
			Arg.setName(argNames[k++]);
		}

		//������
		BasicBlock* BB = BasicBlock::Create(TheContext, "entry", TheFunction);
		Builder.SetInsertPoint(BB);

		for (auto& Arg : TheFunction->args())
			NamedValues[Arg.getName()] = &Arg;

		if (Value* RetVal = childNodes[bodyIdx]->codegen()) {
			Builder.CreateRet(RetVal);
			verifyFunction(*TheFunction);
			return TheFunction;
		}

		TheFunction->eraseFromParent();
		return nullptr;
	}

	//�Ĺ��ķ�֮��assignmentExpression����Ӧ��ֻ��->vari+assignOp+BinOp���������˰�
	case node_type::AssignmentExpression: {
		Value* L = childNodes[0]->codegen();
		Value* R = childNodes[2]->codegen();	
		Value* Tmp;
		string assignOpValue = childNodes[1]->value;
		const char* asValue = assignOpValue.data();
		switch (hash_(asValue))
		{
		case(hash_compile_time("=")): 
			Builder.CreateStore(R, L);
			return nullptr;
		case(hash_compile_time("*=")):
			Tmp = Builder.CreateFMul(L, R, "multmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("/=")):
			Tmp = Builder.CreateFDiv(L, R, "divtmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("%=")):
			Tmp = Builder.CreateSRem(L, R, "remtmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("+=")):
			Tmp = Builder.CreateFAdd(L, R, "addtmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("-=")):
			Tmp = Builder.CreateFSub(L, R, "subtmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("<<=")):
			Tmp = Builder.CreateShl(L, R, "shltmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time(">>=")):
			Tmp = Builder.CreateLShr(L, R, "LShrtmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("&=")):
			Tmp = Builder.CreateAnd(L, R, "andtmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("^=")):
			Tmp = Builder.CreateXor(L, R, "xortmp");
			Builder.CreateStore(R, Tmp);
		case(hash_compile_time("|=")):
			Tmp = Builder.CreateOr(L, R, "ortmp");
			Builder.CreateStore(R, Tmp);
		default:
			return LogErrorV("invalid assignment operator");

		}

	}
	//�����ҷ���LHS�����ٷ�LHS OP RHS ����֪������û�����������Ŀǰ�������ǼӸ��жϿ�����ʲô���о��ֵ�ʱ��Ӧ����һ��binaryexpression����ÿ�һЩ����������Ϊ��ݹ������ȥ����
	case node_type::LHS: {
		node_type firstType = childNodes[0]->type;
		string returnValue;
		//ֱ�Ӵ�Binary Expressionճ������
		if (firstType==node_type::LHS) {
			Value* L = childNodes[0]->codegen();
			Value* R = childNodes[2]->codegen();
			if (!L || !R)
				return nullptr;

			string Op = childNodes[1]->value;
			const char* op = Op.data();

			switch (hash_(op)) {
			case hash_compile_time("+"):
				return Builder.CreateFAdd(L, R, "addtmp");
			case hash_compile_time("-"):
				return Builder.CreateFSub(L, R, "subtmp");
			case hash_compile_time("*"):
				return Builder.CreateFMul(L, R, "multmp");
			case hash_compile_time("/"):
				return Builder.CreateFDiv(L, R, "divtmp");
			case hash_compile_time("%"):
				return Builder.CreateSRem(L, R, "remtmp");
			case hash_compile_time("<<"):
				return Builder.CreateShl(L, R, "shltmp");
			case hash_compile_time(">>"):
				return Builder.CreateLShr(L, R, "lshrtmp");
			case hash_compile_time(">"):
				return Builder.CreateFCmpUGT(L, R, "ugttmp");
			case hash_compile_time(">="):
				return Builder.CreateFCmpUGE(L, R, "ugetmp");
			case hash_compile_time("<"):
				return Builder.CreateFCmpULT(L, R, "ulttmp");
			case hash_compile_time("<="):
				return Builder.CreateFCmpULE(L, R, "uletmp");
			case hash_compile_time("||"):
				return Builder.CreateOr(L, R, "ortmp");
			case hash_compile_time("&&"):
				return Builder.CreateAnd(L, R, "andtmp");
			case hash_compile_time("=="):
				return Builder.CreateICmpEQ(L, R, "equtmp");
			case hash_compile_time("!="):
				return Builder.CreateICmpNE(L, R, "neqtmp");
			case hash_compile_time("^"):
				return Builder.CreateXor(L, R, "xortmp");
				//��λ����Ҳ����������������պ���
			case hash_compile_time("|"):
				return Builder.CreateOr(L, R, "ortmp");
			case hash_compile_time("&"):
				return Builder.CreateAnd(L, R, "andtmp");


				//�����Ʊ��ʽֻ�У�û��д��������һ�²�Ӧ��������ȥд

			default:
				return LogErrorV("invalid binary operator");
			}
		}

		//primaryExpression
		else
		{
			return childNodes[0]->codegen();
		}
	}
	case node_type::RHS: {
		for (int i = 0; i < childNodes.size(); i++) {
			childNodes[i]->codegen();
		}
		return nullptr;
	}
	case node_type::PrimaryExpression: {
		//1.��������ȡ�м�
		node_type type = childNodes[0]->type;
		if (type == node_type::Token) {
			return childNodes[1]->codegen();
		}
		//2.literalexpression���߱���
		else 
		{
			return childNodes[0]->codegen();
		}
	}
	case node_type::BinaryExpression: {
		//ֻ��һ��LHSʱ
		if (childNodes.size() == 1) {
			return childNodes[0]->codegen();
		}
		else
		{
			Value* L = childNodes[0]->codegen();
			Value* R = childNodes[2]->codegen();
			if (!L || !R)
				return nullptr;
			
			string Op = childNodes[1]->value;
			const char* op = Op.data();

			switch (hash_(op)) {
			case hash_compile_time("+"):
				return Builder.CreateFAdd(L, R, "addtmp");
			case hash_compile_time("-"):
				return Builder.CreateFSub(L, R, "subtmp");
			case hash_compile_time("*"):
				return Builder.CreateFMul(L, R, "multmp");
			case hash_compile_time("/"):
				return Builder.CreateFDiv(L, R, "divtmp");
			case hash_compile_time("%"):
				return Builder.CreateSRem(L, R, "remtmp");
			case hash_compile_time("<<"):
				return Builder.CreateShl(L, R, "shltmp");
			case hash_compile_time(">>"):
				return Builder.CreateLShr(L, R, "lshrtmp");
			case hash_compile_time(">"):
				return Builder.CreateFCmpUGT(L, R, "ugttmp");
			case hash_compile_time(">="):
				return Builder.CreateFCmpUGE(L, R, "ugetmp");
			case hash_compile_time("<"):
				return Builder.CreateFCmpULT(L, R, "ulttmp");
			case hash_compile_time("<="):
				return Builder.CreateFCmpULE(L, R, "uletmp");
			case hash_compile_time("||"):
				return Builder.CreateOr(L, R, "ortmp");
			case hash_compile_time("&&"):
				return Builder.CreateAnd(L, R, "andtmp");
			case hash_compile_time("=="):
				return Builder.CreateICmpEQ(L, R, "equtmp");
			case hash_compile_time("!="):
				return Builder.CreateICmpNE(L, R, "neqtmp");
			case hash_compile_time("^"):
				return Builder.CreateXor(L, R, "xortmp");
				//��λ����Ҳ������������������
			case hash_compile_time("|"):
				return Builder.CreateOr(L, R, "ortmp");
			case hash_compile_time("&"):
				return Builder.CreateAnd(L, R, "andtmp");

			

			default:
				return LogErrorV("invalid binary operator");
			}
		}
		
	}
	
	default:
		return ConstantFP::get(Type::getDoubleTy(TheContext), 1.0);
		break;
	}
}
