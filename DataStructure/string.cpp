#include "string.h"

#include <string.h>
#include <iostream>

namespace tw {
String::String(char c) {
  m_content = new char[1];
  m_content[0] = c;
  m_length = 1;
  m_capacity = 1;
}

String::String(const char* str) {
  m_length = strlen(str);
  m_capacity = m_length;
  m_content = new char[m_length];

  for (int i = 0; i < m_length; i++) {
    m_content[i] = str[i];
  }
}

String::String(const String& str) {
  m_length = str.m_length;
  m_capacity = str.m_capacity;
  m_content = new char[m_length];

  for (int i = 0; i < m_length; i++) {
    m_content[i] = str.m_content[i];
  }
}

String::~String() { delete[] m_content; }

void String::print() const {
  for (int i = 0; i < m_length; i++) {
    std::cout << m_content[i];
  }
  std::cout << std::endl;
}

String& String::assign(const String& str) {
  int str_length = str.m_length;
  if (str_length > m_capacity) {
    delete[] m_content;
    m_content = new char[str_length];
    m_capacity = str_length;
  }

  for (int i = 0; i < str_length; i++) {
    m_content[i] = str.m_content[i];
  }

  m_length = str_length;

  return *this;
}

String& String::assign(const char* str) {
  int str_length = strlen(str);
  if (str_length > m_capacity) {
    delete[] m_content;
    m_content = new char[str_length];
    m_capacity = str_length;
  }

  for (int i = 0; i < str_length; i++) {
    m_content[i] = str[i];
  }

  m_length = str_length;

  return *this;
}

void String::reserve(int size) {
  if (size > m_capacity) {
    char* prev_content = m_content;
    m_content = new char[size];
    m_capacity = size;

    for (int i = 0; i < m_length; i++) {
      m_content[i] = prev_content[i];
    }
    delete[] prev_content;
  }
}

char String::at(int idx) const {
  if (idx < 0 || idx > m_length) {
    std::cout << "Wrong Index!" << std::endl;
    return '\0';
  } else {
    return m_content[idx];
  }
}

String& String::insert(int loc, const String& str) {
  if (loc < 0 || loc > m_length) {
    std::cout << "Wrong Location!" << std::endl;
    return *this;
  }

  if (m_length + str.m_length > m_capacity) {
    if (m_capacity * 2 > m_length + str.m_length) {
      m_capacity *= 2;
    } else {
      m_capacity = m_length + str.m_length;
    }
    char* prev_content = m_content;
    m_content = new char[m_capacity];

    int i = 0;
    for (; i < loc; i++) {
      m_content[i] = prev_content[i];
    }
    for (int j = 0; j < str.m_length; j++) {
      m_content[i + j] = str.m_content[j];
    }
    for (; i < m_length + str.m_length; i++) {
      m_content[str.m_length + i] = prev_content[i];
    }

    delete[] prev_content;
  } else {
    for (int i = m_length - 1; i >= loc; i--) {
      m_content[i + str.m_length] = m_content[i];
    }
    for (int i = 0; i < str.m_length; i++) {
      m_content[i + loc] = str.m_content[i];
    }
  }

  m_length += str.m_length;
  return *this;
}

String& String::insert(int loc, const char* str) {
  String tmp(str);
  return insert(loc, tmp);
}

String& String::insert(int loc, char c) {
  String tmp(c);
  return insert(loc, tmp);
}

String& String::erase(int loc, int num) {
  if (loc < 0 || loc > m_length) {
    std::cout << "Wrong Location!" << std::endl;
    return *this;
  }
  if (num < 0) {
    std::cout << "Number must positive value!" << std::endl;
    return *this;
  }

  for (int i = loc + num; i < m_length; i++) {
    m_content[i - num] = m_content[i];
  }
  m_length -= num;
  return *this;
}

int String::find(const String& str, int start) const {
  if (str.m_length == 0) {
    return -1;
  }

  int pos, len;
  for (pos = start; pos <= m_length - str.m_length; pos++) {
    for (len = 0; len < str.m_length; len++) {
      if (m_content[pos + len] != str.m_content[len]) {
        break;
      }
    }
    if (len == str.m_length) {
      return pos;
    }
  }

  return -1;
}

int String::find(const char* str, int start) const {
  String tmp(str);
  return find(tmp, start);
}

int String::find(char c, int start) const {
  String tmp(c);
  return find(tmp, start);
}

int String::compare(const String& str) const {
  for (int i = 0; i < std::min(m_length, str.m_length); i++) {
    if (m_content[i] > str.m_content[i]) {
      return 1;
    } else if (m_content[i] < str.m_content[i]) {
      return -1;
    }
  }

  if (m_length == str.m_length) {
    return 0;
  }

  if (m_length > str.m_length) {
    return 1;
  }
  return -1;
}
}  // namespace tw

int main() {
  tw::String str1("hello world");
  tw::String str2(str1);

  str1.print();
  str2.print();

  tw::String str3("HI!");
  str2.assign(str3);
  str2.print();

  str1.reserve(20);
  std::cout << "Capacity: " << str1.get_capacity() << std::endl;
  std::cout << "Length: " << str1.get_length() << std::endl;

  str1.insert(4, str2);
  str1.print();

  str2.erase(2, 3);
  str2.print();

  tw::String str4("google.com");
  std::cout << "Location of '.' in google.com: " << str3.find('.') << std::endl;

  tw::String str5("abc");
  tw::String str6("abcd");
  std::cout << "Compare 'abc' and 'abcd': " << str1.compare(str2) << std::endl;
}