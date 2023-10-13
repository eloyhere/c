#include <string>
#include <iostream>
namespace number
{
enum Type
{
    zero = 0x0,
    positive = 0x1,
    negative = -0x1
};

class Integer
{
  private:
    mutable Type _type;
    mutable std::string _value;

    void align(std::string *a, std::string *b) const
    {
        if (a->size() != b->size())
        {
            auto shorter = [](std::string *a, std::string *b) -> std::string * {
                return a->size() < b->size() ? a : b;
            };
            const int offset = a->size() < b->size() ? b->size() - a->size() : a->size() - b->size();
            std::string *s = shorter(a, b);
            *s = this->fill('0', offset) + *s;
        }
    }

    std::string fill(const char &character, const int &count) const
    {
        std::string result = "";
        while (result.size() < count)
        {
            result += character;
        }
        return result;
    }

    std::string &internal() const
    {
        return const_cast<std::string &>(this->_value);
    }

    Type typeOf(const long &value) const
    {
        return value == 0 ? Type::zero : (value < 0 ? Type::negative : Type::positive);
    }

    Type typeOf(const std::string &value) const
    {
        if (value == "-0" || value.size() == 0 || value[0] == '0')
        {
            return Type::zero;
        }
        return value[0] == '-' ? Type::negative : Type::positive;
    }

    std::string valueOf(const long &value) const
    {
        return std::to_string(value < 0 ? -value : value);
    }

    std::string valueOf(const std::string &value) const
    {
        std::string result = "";
        for (int i = 0; i < value.size(); i++)
        {
            if (value[i] >= '0' && value[i] <= '9')
            {
                result += value[i];
            }
            while (result.size() > 1 && result[0] == '0')
            {
                result = result.substr(1, result.size() - 1);
            }
        }
        return result;
    }

  public:
    Integer() : _type(Type::zero), _value("0")
    {
    }

    Integer(const bool &value) : _type(this->typeOf(value)), _value(this->valueOf(value))
    {
    }

    Integer(const char &value) : _type(this->typeOf(value)), _value(this->valueOf(value))
    {
    }

    Integer(const char *value) : _type(this->typeOf((std::string)value)), _value(this->valueOf((std::string)value))
    {
    }

    Integer(const short &value) : _type(this->typeOf(value)), _value(this->valueOf(value))
    {
    }

    Integer(const int &value) : _type(this->typeOf(value)), _value(this->valueOf(value))
    {
    }

    Integer(const long &value) : _type(this->typeOf(value)), _value(this->valueOf(value))
    {
    }

    Integer(const std::string &value) : _type(this->typeOf(value)), _value(this->valueOf(value))
    {
    }

    Integer(const Type &type, const std::string &value) : _type(type), _value(this->valueOf(value))
    {
    }

    Integer(const Integer &integer) : _type(integer.type()), _value(this->valueOf(integer._value))
    {
    }

    Integer absolute() const
    {
        if (this->type() == Type::negative)
        {
            return {Type::positive, _value};
        }
        return *this;
    }

    Integer at(const int &i) const
    {
        const int index = ((i % this->size()) + this->size()) % this->size();
        Type type = this->type();
        std::string value = std::to_string((short)(this->_value[i] - '0')) + this->fill('0', this->size() - 1 - index);
        return {type, value};
    }

    std::string binary() const
    {
        Type type = this->type();
        Integer process = this->absolute();
        std::string result = "";

        return (type == Type::negative ? "-" : "") + result;
    }

    Integer fractor(const Integer &number) const
    {
        for (Integer fractor = this->max(number) / 2; fractor > 1; fractor = fractor--)
        {
            if ((*this) % fractor == 0)
            {
                return fractor;
            }
        }
        return 1;
    }

    Integer logarithm() const
    {
        return 0;
    }

    Integer logarithm(const Integer &number) const
    {
        return 0;
    }

    Integer max(const Integer &b) const
    {
        return (*this) > b ? (*this) : b;
    }

    Integer min(const Integer &b) const
    {
        return (*this) < b ? (*this) : b;
    }

    Integer negate() const
    {
        Type type = this->type() == Type::zero ? Type::zero : (this->type() == Type::positive ? Type::negative : Type::positive);
        return {type, _value};
    }

    Integer power(const Integer &pointer) const
    {
        if (pointer < 0)
        {
            return 0;
        }
        else if (pointer == 0)
        {
            return 1;
        }
        else if (pointer == 1)
        {
            return *this;
        }
        Integer result = *this;
        for (Integer p = 1; p < pointer; p = p++)
        {
            result = result * result;
        }
        return result;
    }

    Integer power(const bool &pointer) const
    {
        return pointer ? (*this) : ((Integer)1);
    }

    Integer power(const char &pointer) const
    {
        if (pointer < 0)
        {
            return 0;
        }
        else if (pointer == 0)
        {
            return 1;
        }
        else if (pointer == 1)
        {
            return *this;
        }
        Integer result = *this;
        for (Integer p = 1; p < pointer; p = p++)
        {
            result = result * result;
        }
        return result;
    }

    Integer power(const short &pointer) const
    {
        if (pointer < 0)
        {
            return 0;
        }
        else if (pointer == 0)
        {
            return 1;
        }
        else if (pointer == 1)
        {
            return *this;
        }
        Integer result = *this;
        for (Integer p = 1; p < pointer; p = p++)
        {
            result = result * result;
        }
        return result;
    }

    Integer power(const int &pointer) const
    {
        if (pointer < 0)
        {
            return 0;
        }
        else if (pointer == 0)
        {
            return 1;
        }
        else if (pointer == 1)
        {
            return *this;
        }
        Integer result = *this;
        for (Integer p = 1; p < pointer; p = p++)
        {
            result = result * result;
        }
        return result;
    }

    Integer power(const long &pointer) const
    {
        if (pointer < 0)
        {
            return 0;
        }
        if (pointer == 0)
        {
            return 1;
        }
        Integer result = *this;
        for (Integer p = 1; p < pointer; p = p++)
        {
            result = result * result;
        }
        return result;
    }

    Integer root(const Integer &integer) const
    {
        return 0;
    }

    Integer shift(const int &offset) const
    {
        int o = offset;
        Integer proxy = *this;
        while (this->size() && o)
        {
            proxy = o > 0 ? proxy * (Integer)2 : proxy / (Integer)2;
            o = o > 0 ? o - 1 : o + 1;
        }
        return proxy;
    }

    Integer shift10(const int &offset)
    {
        if (offset == 0)
        {
            return *this;
        }
        Type type = this->type();
        std::string result = this->_value;
        if (offset < 0)
        {
            const int o = (-offset) > result.size() ? result.size() : (-offset);
            return {type, result.substr(0, o)};
        }
        return {type, result + fill('0', offset)};
    }

    int size() const
    {
        return this->_value.size();
    }

    Integer sub(const int &start, const int &end) const
    {
        const int s = start < 0 ? 0 : (start >= this->size() ? this->size() - 1 : start);
        const int e = end < 0 ? start : (end < this->size() ? end : this->size());
        if (s >= e)
        {
            return 0;
        }
        Type type = this->type();
        std::string result = this->absolute().value().substr(s, e) + this->fill('0', this->size() - e);
        return {type, result};
    }

    short valueAt(const int &index) const
    {
        const int i = ((index % this->size()) + this->size()) % this->size();
        return (short)(this->_value[i] - '0');
    }

    std::string value() const
    {
        return this->type() == Type::negative ? "-" + this->_value : this->_value;
    }

    Type type() const
    {
        return this->_type;
    }

    operator bool() const
    {
        return this->size() > 0 && this->_value[0] != '0';
    }

    operator char() const
    {
        char result = 0;
        for (int i = 0; i < this->size(); i++)
        {
            result = result * 10 + this->_value[i] - '0';
        }
        return result;
    }

    operator short() const
    {
        short result = 0;
        for (int i = 0; i < this->size(); i++)
        {
            result = result * 10 + this->_value[i] - '0';
        }
        return result;
    }

    operator int() const
    {
        int result = 0;
        for (int i = 0; i < this->size(); i++)
        {
            result = result * 10 + this->_value[i] - '0';
        }
        return result;
    }

    operator long() const
    {
        long result = 0;
        for (int i = 0; i < this->size(); i++)
        {
            result = result * 10 + this->_value[i] - '0';
        }
        return result;
    }

    operator std::string() const
    {
        return this->type() == Type::negative ? "-" + this->_value : this->_value;
    }

    Integer operator[](const int &index) const
    {
        return this->at(index);
    }

    Integer operator+(const Integer &integer) const
    {
        std::string a = this->_value;
        std::string b = integer._value;
        this->align(&a, &b);
        std::string result = this->fill('0', (a.size() < b.size() ? b.size() : a.size()) + 1);
        Integer absolute1 = this->absolute();
        Integer absolute2 = integer.absolute();
        Type type = absolute1 > absolute2 ? this->type() : integer.type();
        switch (this->type() * integer.type())
        {
        case Type::zero:
            return this->type() == Type::zero ? integer : (*this);
            break;
        case Type::positive:
            for (int i = a.size() - 1; i > -1; i--)
            {
                short bit = ((short)(a[i] - '0') + (short)(b[i] - '0') + (short)(result[i + 1] - '0')) % 10;
                short carry = ((short)(a[i] - '0') + (short)(b[i] - '0') + (short)(result[i + 1] - '0')) / 10;
                result[i] = (char)(carry + '0');
                result[i + 1] = (char)(bit + '0');
            }
            return {type, result};
            break;
        case Type::negative:
            if (absolute1 == absolute2)
            {
                return 0;
            }
            if (absolute1 < absolute2)
            {
                std::string temp = a;
                a = b;
                b = temp;
            }
            for (int i = a.size() - 1; i > -1; i--)
            {
                short bit = ((short)(a[i] - '0') - (short)(b[i] - '0') + (short)(result[i + 1] - '0') + 10) % 10;
                short carry = ((short)(a[i] - '0') - (short)(b[i] - '0') + (short)(result[i + 1] - '0'));
                carry = carry < 0 ? -(carry / 10 + 1) : 0;
                result[i] = (char)(carry + '0');
                result[i + 1] = (char)(bit + '0');
            }
            return {type, result};
            break;
        default:
            return 0;
            break;
        }
    }

    Integer operator+(const bool &value) const
    {
        Integer b = value;
        return (*this) + b;
    }

    Integer operator+(const char &value) const
    {
        Integer b = value;
        return (*this) + b;
    }

    Integer operator+(const short &value) const
    {
        Integer b = value;
        return (*this) + b;
    }

    Integer operator+(const int &value) const
    {
        Integer b = value;
        return (*this) + b;
    }

    Integer operator+(const long &value) const
    {
        Integer b = value;
        return (*this) + b;
    }

    Integer operator+(const std::string &value) const
    {
        Integer b = value;
        return (*this) + b;
    }

    Integer operator++() const
    {
        return (*this) + (Integer)1;
    }

    Integer operator++(int) const
    {
        return (*this) + (Integer)1;
    }

    Integer operator-() const
    {
        Type type = this->type() == Type::zero ? Type::zero : (this->type() == Type::positive ? Type::negative : Type::positive);
        return {type, _value};
    }

    Integer operator-(const Integer &integer) const
    {
        std::string a = this->_value;
        std::string b = integer._value;
        this->align(&a, &b);
        std::string result = this->fill('0', (a.size() < b.size() ? b.size() : a.size()) + 1);
        Integer absolute1 = this->absolute();
        Integer absolute2 = integer.absolute();
        Type type = absolute1 > absolute2 ? this->type() : integer.type();
        switch (this->type() * integer.type())
        {
        case Type::zero:
            return this->type() == Type::zero ? -(integer) : (*this);
            break;
        case Type::positive:
            if (absolute1 == absolute2)
            {
                return 0;
            }
            if (absolute1 < absolute2)
            {
                std::string temp = a;
                a = b;
                b = temp;
            }
            for (int i = a.size() - 1; i > -1; i--)
            {
                short bit = ((short)(a[i] - '0') - (short)(b[i] - '0') + (short)(result[i + 1] - '0') + 10) % 10;
                short carry = ((short)(a[i] - '0') - (short)(b[i] - '0') + (short)(result[i + 1] - '0'));
                carry = carry < 0 ? -(carry / 10 + 1) : 0;
                result[i] = (char)(carry + '0');
                result[i + 1] = (char)(bit + '0');
            }
            return {type, result};
            break;
        case Type::negative:
            for (int i = a.size() - 1; i > -1; i--)
            {
                short bit = ((short)(a[i] - '0') + (short)(b[i] - '0') + (short)(result[i + 1] - '0')) % 10;
                short carry = ((short)(a[i] - '0') + (short)(b[i] - '0') + (short)(result[i + 1] - '0')) / 10;
                result[i] = (char)(carry + '0');
                result[i + 1] = (char)(bit + '0');
            }
            type = (*this) > 0 ? Type::positive : Type::negative;
            return {type, result};
            break;
        default:
            return 0;
            break;
        }
    }

    Integer operator-(const bool &value) const
    {
        Integer b = value;
        return (*this) - b;
    }

    Integer operator-(const char &value) const
    {
        Integer b = value;
        return (*this) - b;
    }

    Integer operator-(const short &value) const
    {
        Integer b = value;
        return (*this) - b;
    }

    Integer operator-(const int &value) const
    {
        Integer b = value;
        return (*this) - b;
    }

    Integer operator-(const long &integer) const
    {
        Integer b = integer;
        return (*this) - b;
    }

    Integer operator-(const std::string &integer) const
    {
        Integer b = integer;
        return (*this) - b;
    }

    Integer operator--() const
    {
        return (*this) - (Integer)1;
    }

    Integer operator--(int) const
    {
        return (*this) - (Integer)1;
    }

    Integer operator*(const Integer &integer) const
    {
        Type type = this->typeOf(this->type() * integer.type());
        if (type == Type::zero)
        {
            return 0;
        }
        std::string value = this->_value;
        if (integer == (Integer)10)
        {
            return {type, _value + "0"};
        }
        Integer result = {type, "0"};
        Integer proxy = *this;
        for (int a = this->size() - 1; a > -1; a--)
        {
            Integer bit = 0;
            for (int b = integer.size() - 1; b > -1; b--)
            {
                short bit1 = this->valueAt(a);
                short bit2 = integer.valueAt(b);
                bit = bit + ((Integer)(bit1 * bit2)).shift10(integer.size() - 1 - b).shift10(this->size() - 1 - a);
            }
            result = result + bit;
        }
        return {type, result._value};
    }

    Integer operator*(const bool &integer) const
    {
        const Integer b = integer;
        return (*this) * b;
    }

    Integer operator*(const char &integer) const
    {
        const Integer b = integer;
        return (*this) * b;
    }

    Integer operator*(const short &integer) const
    {
        const Integer b = integer;
        return (*this) * b;
    }

    Integer operator*(const int &integer) const
    {
        const Integer b = integer;
        return (*this) * b;
    }

    Integer operator*(const std::string &integer) const
    {
        const Integer b = integer;
        return (*this) * b;
    }

    Integer operator*(const long &integer) const
    {
        const Integer b = integer;
        return (*this) * b;
    }

    Integer operator/(const Integer &integer) const
    {
        Type type = this->typeOf(this->type() * integer.type());
        if (type == Type::zero)
        {
            return 0;
        }
        if (integer == 1)
        {
            return *this;
        }
        if (this->absolute() == integer.absolute())
        {
            return type;
        }
        Integer a = this->absolute();
        Integer b = integer.absolute();
        if (a < b)
        {
            return 0;
        }
        while (a.at(-1) == 0 && b.at(-1) == 0)
        {
            a = a.shift10(-1);
            b = b.shift10(-1);
        }
        Integer result = 0;
        for (Integer rest = a; rest >= b;)
        {
            int start = 0;
            int end = start + b.size();
            while (rest.sub(start, end) < b.shift10(rest.size() - end))
            {
                end++;
            }
            Integer multiply = 10;
            Integer bit = b * multiply.shift10(rest.size() - end);
            while (bit > rest.sub(start, end))
            {
                multiply = multiply--;
                bit = b * multiply.shift10(rest.size() - end);
            }
            result = result + multiply.shift10(rest.size() - end);
            rest = rest - bit;
        }
        return {type, result._value};
    }

    Integer operator/(const bool &integer) const
    {
        const Integer b = integer;
        return (*this) / b;
    }

    Integer operator/(const char &integer) const
    {
        const Integer b = integer;
        return (*this) / b;
    }

    Integer operator/(const short &integer) const
    {
        const Integer b = integer;
        return (*this) / b;
    }

    Integer operator/(const int &integer) const
    {
        const Integer b = integer;
        return (*this) / b;
    }

    Integer operator/(const long &integer) const
    {
        const Integer b = integer;
        return (*this) / b;
    }

    Integer operator/(const std::string &integer) const
    {
        const Integer b = integer;
        return (*this) / b;
    }

    Integer operator%(const Integer &integer) const
    {
        if ((*this) == 0 || integer == 0 || integer.absolute() == 1)
        {
            return 0;
        }
        if (integer == 2)
        {
            return this->valueAt(-1) % 2;
        }
        if (integer == 5)
        {
            return this->valueAt(-1) % 5;
        }
        Type type = typeOf(this->type() * integer.type());
        Integer a = this->absolute();
        Integer b = integer.absolute();
        Integer multiply = a / b;
        Integer module = (a - multiply * b).absolute();
        return {type, module._value};
    }

    Integer operator%(const bool &integer) const
    {
        const Integer b = integer;
        return (*this) % b;
    }

    Integer operator%(const char &integer) const
    {
        const Integer b = integer;
        return (*this) % b;
    }

    Integer operator%(const short &integer) const
    {
        const Integer b = integer;
        return (*this) % b;
    }

    Integer operator%(const int &integer) const
    {
        const Integer b = integer;
        return (*this) % b;
    }

    Integer operator%(const long &integer) const
    {
        const Integer b = integer;
        return (*this) % b;
    }

    Integer operator%(const std::string &integer) const
    {
        const Integer b = integer;
        return (*this) % b;
    }

    Integer operator&(const Integer &integer) const
    {
        return 0;
    }

    Integer operator&(const long &integer) const
    {
        return 0;
    }

    Integer operator|(const Integer &integer) const
    {
        return 0;
    }

    Integer operator|(const long &integer) const
    {
        return 0;
    }

    Integer operator~() const
    {
        return 0;
    }

    Integer operator^(const Integer &integer) const
    {
        return 0;
    }

    Integer operator^(const long &integer) const
    {
        return 0;
    }

    Integer operator<<(const Integer &integer) const
    {
        return 0;
    }

    Integer operator<<(const long &integer) const
    {
        return 0;
    }

    Integer operator>>(const Integer &integer) const
    {
        return 0;
    }

    Integer operator>>(const long &integer) const
    {
        return 0;
    }

    bool operator>(const Integer &integer) const
    {
        switch (this->type() * integer.type())
        {
        case Type::zero:
            return (this->type() == Type::positive && integer.type() == Type::zero) || (this->type() == Type::zero && integer.type() == Type::negative);
            break;
        case Type::positive:
            if (this->type() == Type::positive)
            {
                return this->size() > integer.size() || (this->size() == integer.size() && this->_value > integer._value);
            }
            else
            {
                return this->size() < integer.size() || (this->size() == integer.size() && this->_value < integer._value);
            }
            break;
        case Type::negative:
            return this->type() == Type::positive;
            break;
        default:
            return false;
            break;
        }
    }

    friend bool operator>(const Integer &integer, const bool &number)
    {
        const Integer compare = number;
        return integer > compare;
    }

    friend bool operator>(const bool &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer;
    }

    friend bool operator>(const Integer &integer, const char &number)
    {
        const Integer compare = number;
        return integer > compare;
    }

    friend bool operator>(const char &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer;
    }

    friend bool operator>(const Integer &integer, const short &number)
    {
        const Integer compare = number;
        return integer > compare;
    }

    friend bool operator>(const short &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer;
    }

    friend bool operator>(const Integer integer, const int &number)
    {
        const Integer compare = number;
        return integer > compare;
    }

    friend bool operator>(const int &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer;
    }

    friend bool operator>(const Integer integer, const long &number)
    {
        const Integer compare = number;
        return integer > compare;
    }

    friend bool operator>(const long &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer;
    }

    friend bool operator>(const Integer integer, const std::string &number)
    {
        const Integer compare = number;
        return integer > compare;
    }

    friend bool operator>(const std::string &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer;
    }

    bool operator>=(const Integer &integer) const
    {
        return (*this) > integer || (*this) == integer;
    }

    friend bool operator>=(const Integer &integer, const bool &number)
    {
        const Integer compare = number;
        return integer > compare || integer == compare;
    }

    friend bool operator>=(const bool &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer || compare == integer;
    }

    friend bool operator>=(const Integer &integer, const char &number)
    {
        const Integer compare = number;
        return integer > compare || integer == compare;
    }

    friend bool operator>=(const char &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer || compare == integer;
    }

    friend bool operator>=(const Integer &integer, const short &number)
    {
        const Integer compare = number;
        return integer > compare || integer == compare;
    }

    friend bool operator>=(const short &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer || compare == integer;
    }

    friend bool operator>=(const Integer integer, const int &number)
    {
        const Integer compare = number;
        return integer > compare || integer == compare;
    }

    friend bool operator>=(const int &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer || compare == integer;
    }

    friend bool operator>=(const Integer integer, const long &number)
    {
        const Integer compare = number;
        return integer > compare || integer == compare;
    }

    friend bool operator>=(const long &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer || compare == integer;
    }

    friend bool operator>=(const Integer integer, const std::string &number)
    {
        const Integer compare = number;
        return integer > compare || integer == compare;
    }

    friend bool operator>=(const std::string &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare > integer || compare == integer;
    }

    bool operator<(const Integer &integer) const
    {
        switch (this->type() * integer.type())
        {
        case Type::zero:
            return (this->type() == Type::negative && integer.type() == Type::zero) || (this->type() == Type::zero && integer.type() == Type::positive);
            break;
        case Type::positive:
            if (this->type() == Type::positive)
            {
                return this->size() < integer.size() || (this->size() == integer.size() && this->_value < integer._value);
            }
            else
            {
                return this->size() > integer.size() || (this->size() == integer.size() && this->_value > integer._value);
            }
            break;
        case Type::negative:
            return this->type() == Type::positive;
            break;
        default:
            return false;
            break;
        }
    }

    friend bool operator<(const Integer &integer, const bool &number)
    {
        const Integer compare = number;
        return integer < compare;
    }

    friend bool operator<(const bool &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer;
    }

    friend bool operator<(const Integer &integer, const char &number)
    {
        const Integer compare = number;
        return integer < compare;
    }

    friend bool operator<(const char &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer;
    }

    friend bool operator<(const Integer &integer, const short &number)
    {
        const Integer compare = number;
        return integer < compare;
    }

    friend bool operator<(const short &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer;
    }

    friend bool operator<(const Integer &integer, const int &number)
    {
        const Integer compare = number;
        return integer < compare;
    }

    friend bool operator<(const int &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer;
    }

    friend bool operator<(const Integer &integer, const long &number)
    {
        const Integer compare = number;
        return integer < compare;
    }

    friend bool operator<(const long &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer;
    }

    friend bool operator<(const std::string &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer;
    }

    friend bool operator<(const Integer &integer, const std::string &number)
    {
        const Integer compare = number;
        return integer < compare;
    }

    bool operator<=(const Integer &integer) const
    {
        return (*this) < integer || (*this) == integer;
    }

    friend bool operator<=(const Integer &integer, const bool &number)
    {
        const Integer compare = number;
        return integer < compare || integer == compare;
    }

    friend bool operator<=(const bool &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer || integer == compare;
    }

    friend bool operator<=(const Integer &integer, const char &number)
    {
        const Integer compare = number;
        return integer < compare || integer == compare;
    }

    friend bool operator<=(const char &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer || integer == compare;
    }

    friend bool operator<=(const Integer &integer, const short &number)
    {
        const Integer compare = number;
        return integer < compare || integer == compare;
    }

    friend bool operator<=(const short &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer || integer == compare;
    }

    friend bool operator<=(const Integer &integer, const int &number)
    {
        const Integer compare = number;
        return integer < compare || integer == compare;
    }

    friend bool operator<=(const int &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer || integer == compare;
    }

    friend bool operator<=(const Integer &integer, const long &number)
    {
        const Integer compare = number;
        return integer < compare || integer == compare;
    }

    friend bool operator<=(const long &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer || integer == compare;
    }

    friend bool operator<=(const std::string &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare < integer || integer == compare;
    }

    friend bool operator<=(const Integer &integer, const std::string &number)
    {
        const Integer compare = number;
        return integer < compare || integer == compare;
    }

    bool operator==(const Integer &number) const
    {
        return this->size() == number.size() && this->_value == number._value;
    }

    friend bool operator==(const Integer &integer, const bool &number)
    {
        const Integer compare = number;
        return integer == compare;
    }

    friend bool operator==(const bool &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare == integer;
    }

    friend bool operator==(const Integer &integer, const char &number)
    {
        const Integer compare = number;
        return integer == compare;
    }

    friend bool operator==(const char &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare == integer;
    }

    friend bool operator==(const Integer &integer, const short &number)
    {
        const Integer compare = number;
        return integer == compare;
    }

    friend bool operator==(const short &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare == integer;
    }

    friend bool operator==(const Integer &integer, const int &number)
    {
        const Integer compare = number;
        return integer == compare;
    }

    friend bool operator==(const int &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare == integer;
    }

    friend bool operator==(const Integer &integer, const long &number)
    {
        const Integer compare = number;
        return integer == compare;
    }

    friend bool operator==(const long &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare == integer;
    }

    friend bool operator==(const Integer &integer, const std::string &number)
    {
        const Integer compare = number;
        return integer == compare;
    }

    friend bool operator==(const std::string &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare == integer;
    }

    bool operator!=(const Integer &number) const
    {
        return this->size() != number.size() || this->_value != number._value;
    }

    friend bool operator!=(const Integer &integer, const bool &number)
    {
        const Integer compare = number;
        return integer != compare;
    }

    friend bool operator!=(const bool &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare != integer;
    }

    friend bool operator!=(const Integer &integer, const char &number)
    {
        const Integer compare = number;
        return integer != compare;
    }

    friend bool operator!=(const char &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare != integer;
    }

    friend bool operator!=(const Integer &integer, const short &number)
    {
        const Integer compare = number;
        return integer != compare;
    }

    friend bool operator!=(const short &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare != integer;
    }

    friend bool operator!=(const Integer &integer, const int &number)
    {
        const Integer compare = number;
        return integer != compare;
    }

    friend bool operator!=(const int &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare != integer;
    }

    friend bool operator!=(const Integer &integer, const long &number)
    {
        const Integer compare = number;
        return integer != compare;
    }

    friend bool operator!=(const long &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare != integer;
    }

    friend bool operator!=(const Integer &integer, const std::string &number)
    {
        const Integer compare = number;
        return integer != compare;
    }

    friend bool operator!=(const std::string &number, const Integer &integer)
    {
        const Integer compare = number;
        return compare != integer;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Integer number)
    {
        return (stream << (number.type() == Type::negative ? "-" + number._value : number._value));
    }
};

class Decimal
{
  private:
    mutable Integer _child;
    mutable Integer _parent;
    mutable Type _type;

    Type typeOf(const long &value) const
    {
        return value == 0 ? Type::zero : (value > 0 ? Type::positive : Type::negative);
    }

    Integer valueOf(const long &value) const
    {
        return ((Integer)value).absolute();
    }

  public:
    Decimal() : _child(0), _parent(1), _type(Type::zero)
    {
    }

    Decimal(const bool &value) : _child(this->valueOf(value)), _parent(1), _type(this->typeOf(value))
    {
    }

    Decimal(const char &value) : _child(this->valueOf(value)), _parent(1), _type(this->typeOf(value))
    {
    }

    Decimal(const short &value) : _child(this->valueOf(value)), _parent(1), _type(this->typeOf(value))
    {
    }

    Decimal(const int &value) : _child(this->valueOf(value)), _parent(1), _type(this->typeOf(value))
    {
    }

    Decimal(const long &value) : _child(this->valueOf(value)), _parent(1), _type(this->typeOf(value))
    {
    }

    Decimal(const Integer &integer) : _child(integer.absolute()), _parent(1), _type(integer.type())
    {
    }
    
    Decimal(const Decimal& decimal) : _child(decimal.child()), _parent(decimal.parent()), _type(decimal.type())
    {
    }

    Decimal(const Integer &child, const Integer &parent) : _child(child.absolute()), _parent(parent.absolute()), _type(this->typeOf(child.type() * parent.type()))
    {
    }

    Decimal absolute() const
    {
        return {child(), parent()};
    }

    Integer child() const
    {
        return this->_child;
    }

    Integer parent() const
    {
        return this->_parent;
    }

    Decimal shift10(const int &p) const
    {
        if (p == 0)
        {
            return *this;
        }
        else if (p > 0)
        {
            const Integer child = this->child().shift10(p);
            const Integer parent = this->parent();
            return {child, parent};
        }
        else
        {
            const Integer child = this->child();
            const Integer parent = this->parent().shift10(-p);
            return {child, parent};
        }
    }

    Type type() const
    {
        return this->_type;
    }

    std::string value(const int &scale) const
    {
        if (scale == 0)
        {
            return (std::string)(this->child() / this->parent());
        }
        const int s = scale < 1 ? 1 : scale;
        std::string integer = (std::string)(this->child() / this->parent()).absolute();
        std::string decimal = (std::string)(this->child().shift10(s) / this->parent());
        while (decimal.size() < s)
        {
            decimal = decimal + '0';
        }
        return (this->type() == Type::negative ? "-" : "") + integer + "." + decimal;
    }

    Decimal operator+(const Decimal &decimal) const
    {
        const Integer parent = this->parent() * decimal.parent();
        const Integer child = (this->child() * decimal.parent() * this->type()) + (decimal.child() * this->parent() * decimal.type());
        return {child, parent};
    }

    Decimal operator+(const Integer &integer) const
    {
        const Decimal decimal = integer;
        return (*this) + decimal;
    }

    friend Decimal operator+(const Integer &integer, const Decimal &decimal)
    {
        const Decimal d = integer;
        return decimal + d;
    }

    Decimal operator+(const bool &decimal) const
    {
        return (*this) + ((Decimal)decimal);
    }

    Decimal operator+(const char &decimal) const
    {
        return (*this) + ((Decimal)decimal);
    }

    Decimal operator+(const int &decimal) const
    {
        return (*this) + ((Decimal)decimal);
    }

    Decimal operator+(const short &decimal) const
    {
        return (*this) + ((Decimal)decimal);
    }

    Decimal operator+(const long &decimal) const
    {
        return (*this) + ((Decimal)decimal);
    }

    Decimal operator-(const Decimal &decimal) const
    {
        const Integer parent = this->parent() * decimal.parent();
        const Integer child = (this->child() * decimal.parent() * this->type()) - (decimal.child() * this->parent() * decimal.type());
        return {child, parent};
    }

    Decimal operator-(const Integer &integer) const
    {
        const Decimal decimal = integer;
        return (*this) - decimal;
    }

    Decimal operator-(const bool &decimal) const
    {
        return (*this) - ((Decimal)decimal);
    }

    Decimal operator-(const char &decimal) const
    {
        return (*this) - ((Decimal)decimal);
    }

    Decimal operator-(const int &decimal) const
    {
        return (*this) - ((Decimal)decimal);
    }

    Decimal operator-(const short &decimal) const
    {
        return (*this) - ((Decimal)decimal);
    }

    Decimal operator-(const long &decimal) const
    {
        return (*this) - ((Decimal)decimal);
    }

    Decimal operator*(const Decimal &decimal) const
    {
        const Integer parent = this->parent() * decimal.parent();
        const Integer child = this->child() * decimal.child();
        return {child * type(), parent};
    }

    Decimal operator*(const Integer &integer) const
    {
        return {child() * integer, parent()};
    }

    Decimal operator*(const bool &decimal) const
    {
        return {child() * decimal, parent()};
    }

    Decimal operator*(const char &decimal) const
    {
        return {child() * decimal, parent()};
    }

    Decimal operator*(const int &decimal) const
    {
        return {child() * decimal, parent()};
    }

    Decimal operator*(const short &decimal) const
    {
        return {child() * decimal, parent()};
    }

    Decimal operator*(const long &decimal) const
    {
        return {child() * decimal, parent()};
    }

    Decimal operator/(const Decimal &decimal) const
    {
        const Integer parent = this->parent() * decimal.child() * decimal.type();
        const Integer child = this->child() * decimal.parent();
        return {child, parent};
    }

    Decimal operator/(const Integer &decimal) const
    {
        return {child(), parent() * decimal};
    }

    Decimal operator/(const bool &decimal) const
    {
        return {child(), parent() * decimal};
    }

    Decimal operator/(const char &decimal) const
    {
        return {child(), parent() * decimal};
    }

    Decimal operator/(const short &decimal) const
    {
        return {child(), parent() * decimal};
    }

    Decimal operator/(const int &decimal) const
    {
        return {child(), parent() * decimal};
    }

    Decimal operator/(const long &decimal) const
    {
        return {child(), parent() * decimal};
    }

    Decimal power(const Integer &pointer) const
    {
        if (pointer == 0)
        {
            return 1;
        }
        if (pointer < 0)
        {
            Decimal result = ((Decimal)1) / (*this);
            for (int i = -1; pointer < i; i--)
            {
                result = result / (*this);
            }
            return result;
        }
        Decimal result = *this;
        for (int i = 1; pointer > i; i++)
        {
            result = result * (*this);
        }
        return result;
    }

    Decimal power(const bool &pointer) const
    {
        return this->power((Integer)pointer);
    }

    Decimal power(const short &pointer) const
    {
        return this->power((Integer)pointer);
    }

    Decimal power(const int &pointer) const
    {
        return this->power((Integer)pointer);
    }

    Decimal power(const long &pointer) const
    {
        return this->power((Integer)pointer);
    }

    Decimal root(const Integer &integer) const
    {
        if (integer == 0)
        {
            return 1;
        }

        return 0;
    }

    Decimal square() const
    {
        return 0;
    }

    bool operator>(const Decimal &decimal) const
    {
        Decimal a = this->absolute();
        Decimal b = decimal.absolute();
        Type type = this->typeOf(this->type() * decimal.type());
        switch (type)
        {
        case Type::zero:
            return (this->type() == Type::positive && decimal.type() == Type::zero) || (this->type() == Type::zero && decimal.type() == Type::negative);
            break;
        case Type::positive:
            if (this->type() == Type::positive)
            {
                Integer childA = a.child() * this->type() * b.parent();
                Integer childB = b.child() * decimal.type() * a.parent();
                return childA > childB;
            }
            else
            {
                Integer childA = a.child() * this->type() * b.parent();
                Integer childB = b.child() * decimal.type() * a.parent();
                return childA < childB;
            }

            break;
        case Type::negative:
            return this->type() == Type::positive;
            break;
        default:
            return 0;
            break;
        }
    }

    bool operator<(const Decimal &decimal) const
    {
        Decimal a = this->absolute();
        Decimal b = decimal.absolute();
        Type type = this->typeOf(this->type() * decimal.type());
        switch (type)
        {
        case Type::zero:
            return (this->type() == Type::negative && decimal.type() == Type::zero) || (this->type() == Type::zero && decimal.type() == Type::positive);
            break;
        case Type::positive:
            if (this->type() == Type::positive)
            {
                Integer childA = a.child() * this->type() * b.parent();
                Integer childB = b.child() * decimal.type() * a.parent();
                return childA < childB;
            }
            else
            {
                Integer childA = a.child() * this->type() * b.parent();
                Integer childB = b.child() * decimal.type() * a.parent();
                return childA > childB;
            }

            break;
        case Type::negative:
            return this->type() == Type::negative;
            break;
        default:
            return 0;
            break;
        }
    }

    bool operator==(const Decimal &decimal) const
    {
        if (this->type() != decimal.type())
        {
            return false;
        }
        const Integer a = this->child() * decimal.parent() * this->type();
        const Integer b = decimal.child() * this->parent() * decimal.type();
        return a == b;
    }
    
    bool operator!=(const Decimal &decimal) const
    {
        if (this->type() == decimal.type())
        {
            return false;
        }
        const Integer a = this->child() * decimal.parent() * this->type();
        const Integer b = decimal.child() * this->parent() * decimal.type();
        return a != b;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Decimal &decimal)
    {
        if (decimal.type() == Type::negative)
        {
            stream << '-';
        }
        if (decimal.type() == Type::zero)
        {
            stream << 0;
        }
        else if (decimal.parent() == 1)
        {
            stream << decimal.child();
        }
        else
        {
            stream << decimal.child() << '/' << decimal.parent();
        }
        return stream;
    }
};

class Real
{
};

class Complex
{
};
}; // namespace number

/*
using namespace std;
using namespace number;
int main(int argc, char *argv[])
{
    Decimal a = 121;
    std::cout << a.square(6);
    return 0;
}
*/
