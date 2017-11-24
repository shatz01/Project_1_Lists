#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
// #include "CDAL.h"

#include <iostream>

SCENARIO("Empty List Check"){
	GIVEN("Empty list of type int") {

		cop3530::List<int> * list  = new cop3530::PSLL<int>();

		WHEN("length is called") {
			THEN("Length should return 0"){
				REQUIRE(list->length() == 0);
			}
		}
		WHEN("Insert 9 is called at a position 0") {
			list->insert(9,0);
			THEN("Peeking front and back should be 9") {
				REQUIRE(list->peek_front() == 9);
				REQUIRE(list->peek_back() == 9);
			}
		}
		WHEN("Inserting 10 at a position 1") {
			THEN("Exception should be thrown") {
				REQUIRE_THROWS(list->insert(10,1));
			}
		}
		WHEN("Replace is called") {
			THEN("Exception should be thrown, no matter where its called on") {
				REQUIRE_THROWS(list->replace(5,0));
				REQUIRE_THROWS(list->replace(6,-1));
				REQUIRE_THROWS(list->replace(7,1));
				REQUIRE_THROWS(list->replace(50, 50));
			}
		}
		WHEN("Remove is called") {
			THEN("Exception should be thrown, no matter where its called on") {
				REQUIRE_THROWS(list->remove(0));
				REQUIRE_THROWS(list->remove(-1));
				REQUIRE_THROWS(list->remove(1));
				REQUIRE_THROWS(list->remove(50));
			}
		}
		WHEN("pop_front or pop_back is called") {
			THEN("Exception should be thrown") {
				REQUIRE_THROWS(list->pop_front());
				REQUIRE_THROWS(list->pop_back());
			}
		}
		WHEN("Item_at is called") {
			THEN("Exception should be thrown") {
				REQUIRE_THROWS(list->item_at(0));
				REQUIRE_THROWS(list->item_at(-1));
				REQUIRE_THROWS(list->item_at(1));
				REQUIRE_THROWS(list->item_at(50));
			}
		}
		WHEN("peek_front or peek_back is called") {
			THEN("Exception should be thrown") {
				REQUIRE_THROWS(list->peek_front());
				REQUIRE_THROWS(list->peek_back());
			}
		}
		WHEN("is_empty or is_full is called") {
			THEN("is_empty should return true") {
				REQUIRE(list->is_empty() == true);
			}
			THEN("is_full should return false") {
				REQUIRE(list->is_full() == false);
			}
		}
		WHEN("clear is called") {
			THEN("No error should be thrown") {
				REQUIRE_NOTHROW(list->clear());
			}
		}
		WHEN ("Checking if the list contains element 7") {
			bool seven = list->contains(7, [](const int& a, const int& b) {
        					return a == b;
   				   		});
			THEN ("It should return false") {
				REQUIRE (!seven);
			}
		}

		WHEN ("List is made to size 11, then cleared again") {
			for (int i = 0; i < 11; ++i){
				list->insert(i, 0);
			}
			REQUIRE(list->length() == 11);
			list->clear();
			THEN("Rerun all tests") {
				WHEN("length is called") {
					THEN("Length should return 0"){
						REQUIRE(list->length() == 0);
					}
				}
				WHEN("Insert 9 is called at a position 0") {
					list->insert(9,0);
					THEN("Peeking front and back should be 9") {
						REQUIRE(list->peek_front() == 9);
						REQUIRE(list->peek_back() == 9);
					}
				}
				WHEN("Inserting 10 at a position 1") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->insert(10,1));
					}
				}
				WHEN("Replace is called") {
					THEN("Exception should be thrown, no matter where its called on") {
						REQUIRE_THROWS(list->replace(5,0));
						REQUIRE_THROWS(list->replace(6,-1));
						REQUIRE_THROWS(list->replace(7,1));
						REQUIRE_THROWS(list->replace(50, 50));
					}
				}
				WHEN("Remove is called") {
					THEN("Exception should be thrown, no matter where its called on") {
						REQUIRE_THROWS(list->remove(0));
						REQUIRE_THROWS(list->remove(-1));
						REQUIRE_THROWS(list->remove(1));
						REQUIRE_THROWS(list->remove(50));
					}
				}
				WHEN("pop_front or pop_back is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->pop_front());
						REQUIRE_THROWS(list->pop_back());
					}
				}
				WHEN("Item_at is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->item_at(0));
						REQUIRE_THROWS(list->item_at(-1));
						REQUIRE_THROWS(list->item_at(1));
						REQUIRE_THROWS(list->item_at(50));
					}
				}
				WHEN("peek_front or peek_back is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->peek_front());
						REQUIRE_THROWS(list->peek_back());
					}
				}
				WHEN("is_empty or is_full is called") {
					THEN("is_empty should return true") {
						REQUIRE(list->is_empty() == true);
					}
					THEN("is_full should return false") {
						REQUIRE(list->is_full() == false);
					}
				}
				WHEN("clear is called") {
					THEN("No error should be thrown") {
						REQUIRE_NOTHROW(list->clear());
					}
				}
				WHEN ("Checking if the list contains element 7") {
					bool seven = list->contains(7, [](const int& a, const int& b) {
		        					return a == b;
		   				   		});
					THEN ("It should return false") {
						REQUIRE (!seven);
					}
				}
			}
		} // end rerun after size 11 list is cleared


		WHEN ("List is made to size 11, then cleared again") {
			for (int i = 0; i < 51; ++i){
				list->insert(i, 0);
			}
			REQUIRE(list->length() == 51);
			list->clear();
			THEN("Rerun all tests") {
				WHEN("length is called") {
					THEN("Length should return 0"){
						REQUIRE(list->length() == 0);
					}
				}
				WHEN("Insert 9 is called at a position 0") {
					list->insert(9,0);
					THEN("Peeking front and back should be 9") {
						REQUIRE(list->peek_front() == 9);
						REQUIRE(list->peek_back() == 9);
					}
				}
				WHEN("Inserting 10 at a position 1") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->insert(10,1));
					}
				}
				WHEN("Replace is called") {
					THEN("Exception should be thrown, no matter where its called on") {
						REQUIRE_THROWS(list->replace(5,0));
						REQUIRE_THROWS(list->replace(6,-1));
						REQUIRE_THROWS(list->replace(7,1));
						REQUIRE_THROWS(list->replace(50, 50));
					}
				}
				WHEN("Remove is called") {
					THEN("Exception should be thrown, no matter where its called on") {
						REQUIRE_THROWS(list->remove(0));
						REQUIRE_THROWS(list->remove(-1));
						REQUIRE_THROWS(list->remove(1));
						REQUIRE_THROWS(list->remove(50));
					}
				}
				WHEN("pop_front or pop_back is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->pop_front());
						REQUIRE_THROWS(list->pop_back());
					}
				}
				WHEN("Item_at is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->item_at(0));
						REQUIRE_THROWS(list->item_at(-1));
						REQUIRE_THROWS(list->item_at(1));
						REQUIRE_THROWS(list->item_at(50));
					}
				}
				WHEN("peek_front or peek_back is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->peek_front());
						REQUIRE_THROWS(list->peek_back());
					}
				}
				WHEN("is_empty or is_full is called") {
					THEN("is_empty should return true") {
						REQUIRE(list->is_empty() == true);
					}
					THEN("is_full should return false") {
						REQUIRE(list->is_full() == false);
					}
				}
				WHEN("clear is called") {
					THEN("No error should be thrown") {
						REQUIRE_NOTHROW(list->clear());
					}
				}
				WHEN ("Checking if the list contains element 7") {
					bool seven = list->contains(7, [](const int& a, const int& b) {
		        					return a == b;
		   				   		});
					THEN ("It should return false") {
						REQUIRE (!seven);
					}
				}
			}
		} // end rerun after size 51 list is cleared

		WHEN ("List is made to size 11, then cleared again") {
			for (int i = 0; i < 1000; ++i){
				list->insert(i, 0);
			}
			REQUIRE(list->length() == 1000);
			list->clear();
			THEN("Rerun all tests") {
				WHEN("length is called") {
					THEN("Length should return 0"){
						REQUIRE(list->length() == 0);
					}
				}
				WHEN("Insert 9 is called at a position 0") {
					list->insert(9,0);
					THEN("Peeking front and back should be 9") {
						REQUIRE(list->peek_front() == 9);
						REQUIRE(list->peek_back() == 9);
					}
				}
				WHEN("Inserting 10 at a position 1") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->insert(10,1));
					}
				}
				WHEN("Replace is called") {
					THEN("Exception should be thrown, no matter where its called on") {
						REQUIRE_THROWS(list->replace(5,0));
						REQUIRE_THROWS(list->replace(6,-1));
						REQUIRE_THROWS(list->replace(7,1));
						REQUIRE_THROWS(list->replace(50, 50));
					}
				}
				WHEN("Remove is called") {
					THEN("Exception should be thrown, no matter where its called on") {
						REQUIRE_THROWS(list->remove(0));
						REQUIRE_THROWS(list->remove(-1));
						REQUIRE_THROWS(list->remove(1));
						REQUIRE_THROWS(list->remove(50));
					}
				}
				WHEN("pop_front or pop_back is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->pop_front());
						REQUIRE_THROWS(list->pop_back());
					}
				}
				WHEN("Item_at is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->item_at(0));
						REQUIRE_THROWS(list->item_at(-1));
						REQUIRE_THROWS(list->item_at(1));
						REQUIRE_THROWS(list->item_at(50));
					}
				}
				WHEN("peek_front or peek_back is called") {
					THEN("Exception should be thrown") {
						REQUIRE_THROWS(list->peek_front());
						REQUIRE_THROWS(list->peek_back());
					}
				}
				WHEN("is_empty or is_full is called") {
					THEN("is_empty should return true") {
						REQUIRE(list->is_empty() == true);
					}
					THEN("is_full should return false") {
						REQUIRE(list->is_full() == false);
					}
				}
				WHEN("clear is called") {
					THEN("No error should be thrown") {
						REQUIRE_NOTHROW(list->clear());
					}
				}
				WHEN ("Checking if the list contains element 7") {
					bool seven = list->contains(7, [](const int& a, const int& b) {
		        					return a == b;
		   				   		});
					THEN ("It should return false") {
						REQUIRE (!seven);
					}
				}
			}
		} // end rerun after size 1000 list is cleared
	}
}

SCENARIO("One element list check") {
	GIVEN( "List with only one element of type string in it ") {

		cop3530::List<std::string> *list = new cop3530::PSLL<std::string>();
		list->push_back("hay there jak");

		WHEN("length is called") {
			THEN("Length should return 1"){
				REQUIRE(list->length() == 1);
			}
		}
		WHEN("Item at is called") {
			THEN("Item at 0 should be hay there jak"){
				REQUIRE(list->item_at(0) == "hay there jak");
			}
			THEN("Any other item_at should result in an exception"){
				REQUIRE_THROWS(list->item_at(-1));
				REQUIRE_THROWS(list->item_at(1));
				REQUIRE_THROWS(list->item_at(50));
			}
		}
		WHEN("peek_front and push back are called") {
			THEN("Both should be hay there jak"){
				REQUIRE(list->peek_front() == "hay there jak");
				REQUIRE(list->peek_back() == "hay there jak");
			}
		}
		WHEN("is_empty and is_full are called") {
			THEN("Both should return false") {
				REQUIRE(!(list->is_full()));
				REQUIRE(!(list->is_empty()));
			}
		}
		WHEN("Popping from front") {
			THEN("Should return hay there jak and length should be zero after each one") {
				REQUIRE(list->pop_front() == "hay there jak");
				REQUIRE(list->length() == 0);
			}
		}
		WHEN("Popping from back") {
			THEN("Should return hay there jak and length should be zero after each one") {
				REQUIRE(list->pop_back() == "hay there jak");
				REQUIRE(list->length() == 0);
			}
		}
		WHEN("Calling remove") {
			THEN("Removing any element other that 0 should result in error") {
				REQUIRE_THROWS(list->remove(-1));
				REQUIRE_THROWS(list->remove(1));
			}
			THEN("Actually removing 0th element") {
				REQUIRE(list->remove(0) == "hay there jak");
				REQUIRE(list->length() == 0);
			}

		}
		WHEN("Pop from list and then push_back 4 elements to the list") {
			list->pop_front();
			list->push_back("w");
			list->push_back("x");
			list->push_back("y");
			list->push_back("z");
			THEN("Indecies should be equal to expected") {
				std::string expected[4] = {"w", "x", "y", "z"};
				for (int i = 0; i < list->length(); ++i)
				{
					REQUIRE(list->item_at(i) == expected[i]);
				}
			}
			WHEN("Clear list and push all the elements to the front instead") {
				list->print(std::cout);

				list->clear();
				list->push_front("w");
				list->push_front("x");
				list->push_front("y");
				list->push_front("z");
				THEN("Indecies should be equal to expected") {
					std::string expected[4] = {"z", "y", "x", "w"};
					for (int i = 0; i < list->length(); ++i)
					{
						REQUIRE(list->item_at(i) == expected[i]);
					}
				}
			}
		}
		WHEN("Replace is called") {
			REQUIRE_THROWS(list->replace("kden", -1));
			REQUIRE_THROWS(list->replace("kden", 1));
			REQUIRE(list->replace("okay", 0) == "hay there jak");
			THEN("item_at 0 should be okay") {
				REQUIRE(list->item_at(0) == "okay");
			}


		}
		WHEN ("Contains is called on the element in there") {
			bool hay_there = list->contains("hay there jak", [](const std::string& a, const std::string& b) {
        					return a == b;
   				   		});
			THEN ("It should return true") {
				REQUIRE (hay_there);
			}
		}
		WHEN ("Contains is called on the element NOT in there") {
			bool k_den = list->contains("kden", [](const std::string& a, const std::string& b) {
        					return a == b;
   				   		});
			THEN ("It should return true") {
				REQUIRE (!k_den);
			}
		}


	}
}

SCENARIO("List of 1001 elements test") {
	GIVEN("List of 1001 integers numbered 0-1000") {
		cop3530::List<int> *list = new cop3530::PSLL<int>();
		for (int i = 0; i < 1001; ++i) {
			list->push_front(i);
		}

		WHEN("Checking length, head, tail, item_at") {
			THEN("Length should be 1001") {
				REQUIRE(list->length() == 1001);
			}
			THEN("Checking head") {
				REQUIRE(list->peek_front() == 1000);
			}
			THEN("Checking item_at") {
				REQUIRE(list->item_at(0) == 1000);
				REQUIRE(list->item_at(1000) == 0);
				REQUIRE_THROWS(list->item_at(1001));
				REQUIRE(list->item_at(49) == 951);
			}
			THEN("Checking tail") {
				REQUIRE(list->peek_back() == 0);
			}
		}
		WHEN(	"popping front and then checking length, head, tail") {
			REQUIRE(list->pop_front() == 1000);
			THEN("Length should be 1000") {
				REQUIRE(list->length() == 1000);
			}
			THEN("Checking head") {
				REQUIRE(list->peek_front() == 999);
			}
			THEN("Checking item_at") {
				REQUIRE(list->item_at(0) == 999);
				REQUIRE(list->item_at(999) == 0);
				REQUIRE_THROWS(list->item_at(1000));
				REQUIRE(list->item_at(49) == 950);
			}
			THEN("Checking tail") {
				REQUIRE(list->peek_back() == 0);
			}
		}
		WHEN("Popping last element then checking length, head, tail") {
			REQUIRE(list->pop_back() == 0);
			THEN("Length should be 1000") {
				REQUIRE(list->length() == 1000);
			}
			THEN("Checking head") {
				REQUIRE(list->peek_front() == 1000);
			}
			THEN("Checking item_at") {
				REQUIRE(list->item_at(0) == 1000);
				REQUIRE(list->item_at(999) == 1);
				REQUIRE_THROWS(list->item_at(1000));
				REQUIRE(list->item_at(49) == 951);
			}
			THEN("Checking tail") {
				REQUIRE(list->peek_back() == 1);
			}
		}
		WHEN("Removing last element then checking length, head, tail") {
			REQUIRE(list->remove(1000) == 0);
			THEN("Length should be 1000") {
				REQUIRE(list->length() == 1000);
			}
			THEN("Checking head") {
				REQUIRE(list->peek_front() == 1000);
			}
			THEN("Checking item_at") {
				REQUIRE(list->item_at(0) == 1000);
				REQUIRE(list->item_at(999) == 1);
				REQUIRE_THROWS(list->item_at(1000));
				REQUIRE(list->item_at(49) == 951);
			}
			THEN("Checking tail") {
				REQUIRE(list->peek_back() == 1);
			}
		}
		WHEN("Removing last element TWICE then checking length, head, tail") {
			REQUIRE(list->pop_back() == 0);
			REQUIRE(list->remove(999) == 1);

			THEN("Length should be 1000") {
				REQUIRE(list->length() == 999);
			}
			THEN("Checking head") {
				REQUIRE(list->peek_front() == 1000);
			}
			THEN("Checking item_at") {
				REQUIRE(list->item_at(0) == 1000);
				REQUIRE(list->item_at(998) == 2);
				REQUIRE_THROWS(list->item_at(999));
				REQUIRE(list->item_at(49) == 951);
			}
			THEN("Checking tail") {
				REQUIRE(list->peek_back() == 2);
			}
		}
	}
}

// 0-49, 50-99, 100-149,... ,950-999, 1000-1049;

SCENARIO ("INTERFACE TEST") {
	GIVEN ("List of characters") {

		cop3530::List<char> * list  = new cop3530::PSLL<char>();
		// cop3530::List<char> * list = new cop3530::PSLL<char>();
		// cop3530::List<char> * list = new cop3530::CDAL<char>();
		// cop3530::List<char> * list = new cop3530::CDAL<char>();
		// cop3530::List<char> * list = new cop3530::CDAL<char>();

		list->insert('A', 0);
		list->insert('B', 1);
		list->push_back('C');
		list->push_front('D');

		WHEN ("Peek front is called") {
			char front = list->peek_front();
			THEN ("Item should be D") {
				REQUIRE(front == 'D');
			}
		}
		WHEN ("Peek back is called") {
			char back = list->peek_back();
			THEN ("Item should be C") {
				REQUIRE(back == 'C');
			}
		}
		WHEN ("Replaced is called with item E at position 1") {
			list->replace('E', 1);
			char item = list->item_at(1);
			THEN ("Item at position 1 should be E") {
				REQUIRE( item == 'E');
			}
		}
		WHEN ("List length is checked") {
			size_t len = list->length();
			THEN ("Length should be 4") {
				REQUIRE( len == 4);
			}
		}
		WHEN ("Checking if list is empty") {
			bool empty = list->is_empty();
			THEN ("It should return false") {
				REQUIRE(!empty);
			}
		}
		WHEN ("Checking if list is full") {
			bool full = list->is_full();
			THEN ("It should return false") {
				REQUIRE(!full);
			}
		}
		WHEN ("Remove is called at position 0") {
			char item = list->remove(0);
			size_t len = list->length();
			THEN ("Item should be D") {
				REQUIRE(item == 'D');
			}
			THEN ("Length should be 3") {
				REQUIRE(len == 3);
			}
		}
		WHEN ("Checking if the list contains element B") {
			bool b = list->contains('B', [](const char& a, const char& b) {
        					return a == b;
   				   		});
			THEN ("It should return true") {
				REQUIRE (b);
			}
		}
		WHEN ("Contents is called on array") {
			char * arr = list->contents();
			THEN ("Array items should be [D, A, B, C]") {
				char expected[4] = {'D', 'A', 'B', 'C'};
				for(size_t i = 0; i < list->length(); i++) {
					REQUIRE(*(arr+i) == expected[i]);
				}
			}
			delete[] arr;
		}
		WHEN ("Clear is called") {
			list->clear();
			size_t len = list->length();
			THEN ("Length should be 0") {
				REQUIRE(len == 0);
			}
			WHEN ("Fill list up to 50 slots"){
				for (int i = 0; i < 50; ++i)
					list->push_back('z');
				size_t len = list->length();
				THEN("Length should be 50") {
					REQUIRE(len == 50);
				}
				THEN("Pop one off the back") {
					list->pop_back();
					size_t len = list->length();
					REQUIRE(len == 49);
					THEN("Push to either side of the list") {
						list->push_front('a');
						list->push_back('b');
						size_t len = list->length();
						REQUIRE(len == 51);
						THEN("Check that the first element is a") {
							bool front_check = list->peek_front() == 'a';
							REQUIRE(front_check);
						}
						THEN ("Check that last element is b") {
							bool back_check = list->peek_back() == 'b';
							REQUIRE(back_check);
						}
						THEN ("Check that 6th element is z") {
							bool six_check = list->item_at(6) == 'z';
							REQUIRE(six_check);
						}
					}
				}
			}
		}

		delete list;
	}
}


SCENARIO ("TEST 1") {
	GIVEN ("List of integers") {

		cop3530::List<int> * list = new cop3530::PSLL<int>();
		// cop3530::List<char> * list = new cop3530::PSLL<char>();
		// cop3530::List<char> * list = new cop3530::CDAL<char>();
		// cop3530::List<char> * list = new cop3530::CDAL<char>();
		// cop3530::List<char> * list = new cop3530::CDAL<char>();

		for(int i = 0; i < 10; i++)
			list->insert(i, 0);

		WHEN ("List length is checked") {
			size_t len = list->length();
			THEN ("Length should be 10") {
				REQUIRE(len == 10);
			}
		}
		WHEN ("Peek front is called") {
			int front = list->peek_front();
			THEN ("Item at the front should be 9") {
				REQUIRE(front == 9);
			}
		}
		WHEN ("Peek back is called") {
			int back = list->peek_back();
			THEN ("Item at the back should be 0") {
				REQUIRE(back == 0);
			}
		}

		delete list;
	}
}
