#include<iostream>
#include "Object.h"
using namespace std;

Object multTest()
{

	Object retValue$;
	retValue$ = (Object(7) * Object(2));
	return retValue$;

}

Object plusTest(Object n)
{

	Object retValue$;
	retValue$ = (n + Object(4) + Object(6));
	return retValue$;

}

Object plusMultTest(Object n)
{

	Object retValue$;
	retValue$ = (retValue$ = (n * Object(17)) + n + retValue$ = (Object(8) * Object(92)));
	retValue$ = (n + Object(4) + Object(6));
	return retValue$;

}

Object ifstmt(Object a, Object b)
{

	Object retValue$;
	if((a < b))
	{
		retValue$ = a;
	}
	else
	{
		retValue$ = b;
	}

	if((a >= b))
	{
		retValue$ = b;
	}

	return retValue$;

}

Object funcAll(Object a, Object b, Object c)
{

	Object retValue$;
	retValue$ = plusTest(a, b);
	return retValue$;

}

