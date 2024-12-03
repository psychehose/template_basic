//
//  main.cpp
//  template_2
//
//  Created by 김호세 on 12/3/24.
//


#include <iostream>
#include <string>

template <typename T>
void print(T arg) {
  std::cout << arg << std::endl;
}

//void print() {
//  std::cout << std::endl;
//}

template <typename T, typename... Types> // ...을 parameter 팩이라고 함.
void print(T arg, Types... args) {
  std::cout << arg << ", ";
  print(args...);
}

// 두 템플릿 메서드 순서를 바꾸면 컴파일 에러 발생 왜?

// 예시로 1, 3.1, "abc"
// std::count << 1 << ", ";
// print(3.1, "abc")
// 으로 변한다. 근데 이걸 쭉쭉 하다보면
// std::cout << "abc" << ", "
// print()가 나온다. print()는 정의 되어 있지 않아서 안됨. 그래서 순서 중요시


size_t GetStringSize(const char* s) { return  strlen(s); }
size_t GetStringSize(const std::string s) { return s.size(); }

void AppendToString(std::string* concat_str) { return; }
template <typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings... strs) {
  concat_str->append(s);
  AppendToString(concat_str, strs...);
}


template <typename String, typename ... Strings>
size_t GetStringSize(const String& s, Strings... strs) {
  return GetStringSize(s) + GetStringSize(strs...);
}

template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs) {
  size_t total_size = GetStringSize(s, strs...);

  std::string concat_str;
  concat_str.reserve(total_size);

  concat_str = s;
  AppendToString(&concat_str, strs...);

  return concat_str;

}


/*
가변 길이 템플릿은 편함. 당연히 단점도 존재
재귀함수 형태로 구성해야해서 재귀 호출 종료 코드 있어야함.. 근데? C++ 17에서 Fold
*/

//int sum_all() { return 0; }
//
//template <typename... Ints>
//int sum_all(int num, Ints... nums) {
//  return num + sum_all(nums...);
//}

template <typename... Ints>
int sum_all(Ints... nums) {
  return (nums + ...);
}
#include <iostream>

class A {
 public:
  void do_something(int x) const {
    std::cout << "Do something with " << x << std::endl;
  }
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums) {
  // 각각의 인자들에 대해 do_something 함수들을 호출한다.
  (... , t.do_something(nums));
}


int main(int argc, const char * argv[]) {
//  // std::string 과 const char* 을 혼합해서 사용 가능하다.
//  std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
//                      " ", std::string("sentence"));

  std::cout << sum_all(1,4,2,3,10) << std::endl;

  A a;
  do_many_things(a, 1, 3, 2, 4);

  return 0;
}
