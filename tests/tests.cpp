/*
MIT License

Copyright (c) 2018 Jukka-Pekka Sarjanen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef ARDUINO
#include<iostream>
#include <iomanip>
#include "UnitTest++/UnitTest++.h"

#define private public
#include "../eventqueue.h"




SUITE(QueueSuite)
{
    class TestFixture{
    public:
       EventQueue<uint8_t,20> _eq;
       TestFixture()
       {
          ;
       }
    };
    TEST_FIXTURE(TestFixture,test_putAndGet)
    {
        uint8_t val=66;
        uint8_t newVal=0;

        CHECK( _eq.putQ(val));
        CHECK( _eq.getQ(newVal));
        CHECK_EQUAL(val,newVal);

        CHECK( _eq.getQ(newVal) == false);

    }
    TEST_FIXTURE(TestFixture,test_putAndGetComplex)
    {
        uint8_t val=0;
        uint8_t newVal=0;
        for (int i = 0; i< _eq._s*2;i++){
            val = i;
            CHECK( _eq.putQ(val));
            CHECK( _eq.getQ(newVal));
            CHECK_EQUAL(val,newVal);
            CHECK( _eq._in < _eq._s);
            CHECK( _eq._out < _eq._s);
            CHECK( _eq.getQ(newVal) == false);
        }

    }
    TEST_FIXTURE(TestFixture,test_putAndGetMoreComplex)
    {

        uint8_t newVal=0;

        for(int j=0; j<3;j++){
            for (int i = 0; i< _eq._s/2;i++){
                CHECK( _eq.putQ(i));

            }
            //Check that we get out what we put
            for (int i = 0; i< _eq._s/2;i++){
                CHECK( _eq.getQ(newVal));
                CHECK_EQUAL(i,newVal);
            }
        }

    }
    TEST_FIXTURE(TestFixture,test_queueOverflow)
    {

        uint8_t newVal=98;
        uint8_t theVal=66;

        for (int i = 0; i< _eq._s;i++){
            CHECK( _eq.putQ(i));
        }

        //Queue full so this shall fail
        CHECK( !_eq.putQ(theVal));

        //pop first out
        CHECK( _eq.getQ(newVal));
        CHECK_EQUAL(0,newVal);


        //Queue not full anymore
        CHECK( _eq.putQ(theVal));

        //pop first out
        CHECK( _eq.getQ(newVal));
        CHECK_EQUAL(1,(int)newVal);

    }

}
#endif
