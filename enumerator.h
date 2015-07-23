/**enumerator.h
 * description: 枚举器
 * author: chorulex
 * date: 07/23/2015
 */

template<typename T>
class enumerator
{
public:
	enumerator() : _current(0) {}
	virtual ~enumerator() {}

protected:
	int _current;

public:
	virtual bool has_more() const = 0;
	virtual T& next() = 0;
};
