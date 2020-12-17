#include "ListOnArray.h"
#include <gtest.h>

TEST(list, can_create_list)
{
	ASSERT_NO_THROW(ListOnArray<int> lst);
}

TEST(list, can_copy)
{
	ListOnArray<int> lst;
	lst.push_back(101);

	ListOnArray<int> lst2(lst);

	EXPECT_EQ(101, lst2[0]);
}

TEST(list, cant_pop_in_empty_list)
{
	ListOnArray<int> lst;
	ASSERT_ANY_THROW(lst.pop_back());
}

TEST(list, can_push_back)
{
	ListOnArray<int> lst(10);

	lst.push_back(23);
	lst.push_back(100);

	EXPECT_EQ(100, lst.pop_back());
}

TEST(list, can_push_front)
{
	ListOnArray<int> lst(10);

	lst.push_back(1);
	lst.push_front(10);

	EXPECT_EQ(10, lst.pop_front());
}

TEST(list, can_pop_front)
{
	ListOnArray<int> lst(10);

	lst.push_back(3);
	lst.push_back(1);
	lst.push_back(5);
	lst.pop_front();

	EXPECT_EQ(1, lst.pop_front());
}

TEST(list, can_pop_back)
{
	ListOnArray<int> lst(10);

	lst.push_back(67);
	lst.push_back(12);
	lst.pop_back();

	EXPECT_EQ(67, lst.pop_back());
}