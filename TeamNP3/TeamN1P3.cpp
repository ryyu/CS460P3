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
	retValue$ = ((n * Object(17)) + n + (Object(8) * Object(92)));
	retValue$ = (Object(2) + Object(2));
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
	retValue$ = plusTest(a);
	return retValue$;

}

Object predCheck(Object b)
{

	Object retValue$;
	if(nullp(b))
	{
		retValue$ = b;
	}

	if(!(listp(b)))
	{
		retValue$ = Object(7);
	}

	return retValue$;

}

Object consTest(Object a)
{

	Object retValue$;
	retValue$ = cons(Object("abcxyz"), Object("( 1 2 3 4 5)"));
	return retValue$;

}

Object coutTest()
{

	Object retValue$;
	cout << (retValue$ = plusTest(Object(2)));
	return retValue$;

}

Object listopTest(Object mylist)
{

	Object retValue$;
	retValue$ = listop("cdr", Object("( a b c)"));
	retValue$ = listop("cdr", Object("( d e f)"));
	retValue$ = listop("car", listop("cdr", mylist));
	return retValue$;

}

int main()
{

	Object retValue$;
	;
	retValue$ = return retValue$;

}

