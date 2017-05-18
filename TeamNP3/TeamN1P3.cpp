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

    return retValue$;

}

Object funcAll(Object a, Object b, Object c)
{

    Object retValue$;
    plusTest(retValue$ = a);
    return retValue$;

}

Object predCheck(Object b)
{

    Object retValue$;
    if(nullp(b))
    {
        retValue$ = b;
    }
    else
    {
        if(!(listp(b)))
        {
            retValue$ = Object(7);
        }
        else
        {
            if(symbolp(b))
            {
                retValue$ = Object(8);
            }
            else
            {
                if((b > Object(8)))
                {
                    retValue$ = Object(9);
                }
                else
                {
                    (Object(2) + Object(2))
                }

            }

        }

    }

    return retValue$;

}

Object consTest(Object lst)
{

    Object retValue$;
    retValue$ = cons(lst, Object("( 1 2 3 4 5)"));
    return retValue$;

}

Object coutTest()
{

    Object retValue$;
    cout << (plusTest(Object(2)));
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
    cout << (Object("Hello_world"));
    cout << endl;
    cout << (multTest());
    cout << endl;
    cout << (plusTest(Object(5)));
    cout << endl;
    cout << (plusMultTest(Object(17)));
    cout << endl;
    cout << (ifstmt(Object(1), Object(3)));
    cout << endl;
    cout << (funcAll(Object(28), Object(31), Object(34)));
    cout << endl;
    cout << (predCheck(Object("()")));
    cout << endl;
    cout << (consTest(Object("( a b c)")));
    cout << endl;
    coutTest();
    cout << endl;
    cout << (listopTest(Object("( a b c)")));
    return retValue$;

}

