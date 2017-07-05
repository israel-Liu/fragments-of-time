class TypesInitiation
{ // http://en.cppreference.com/w/cpp/language/type
public:
	operator char()
	{
		return '';
	}
	
	operator int()
	{
		return 0;
	}
	
	operator double()
	{
		return 0.0;
	}
	
	operator bool()
	{
		return nullptr;
	}
	
	operator auto()
	{
		return "";
	}
};