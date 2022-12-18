#ifndef TW_DATA_STRUCTURE_STRING
#define TW_DATA_STRUCTURE_STRING

namespace tw {
class String {
public:
    explicit String(char c);
    explicit String(const char* str);
    explicit String(const String &str);
    ~String();

    int get_length() const { return m_length; }
    int get_capacity() const { return m_capacity; }

    String& assign(const String &str);
    String& assign(const char* str);
    void reserve(int size);
    char at(int idx) const;
    String& insert(int loc, const String &str);
    String& insert(int loc, const char* str);
    String& insert(int loc, char c);
    String& erase(int loc, int num);
    int find(const String &str, int start = 0) const;
    int find(const char* str, int start = 0) const;
    int find(char c, int start = 0) const;
    int compare(const String &str) const;

    void print() const;

private:
    char* m_content;
    int m_length;
    int m_capacity;
};
} // namespace tw
#endif // TW_DATA_STRUCTURE_STRING