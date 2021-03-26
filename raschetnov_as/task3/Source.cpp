#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

void errorHandler(double* pointer);
void errorHandler(double* _lowerlimit, double* _upperlimit);


class IntegralCalculus
{
  double(*function)(double point);
  int amountOfSubIntervals;
  double result;
  double* limits;
  double leftRiemannSum();
  double middleRiemannSum();
  double rightRiemannSum();
public:
  IntegralCalculus(double (*function)(double point) = exp, int _amountOfSubIntervals = 0, double* _limits = nullptr, double _result = 0): function(function), amountOfSubIntervals(_amountOfSubIntervals), limits(_limits), result(_result)
  {
    bool flag = 1;
    if(_limits != nullptr)
    while(flag)
    {
      flag = 0;
      try
      {
        if(_limits[0] > _limits[1])
          throw 1.0;
      }
      catch(const double error)
      {
        cout << "Lower limit more then upper limit: " << endl;
        errorHandler(_limits);
        if(_limits[0] < _limits[1])
        {
          limits[0] = _limits[0];
          limits[1] = _limits[1];
        }
        else
          flag = 1;
      }
    }
    limits = new double[2];
    limits[0] = 0;
    limits[1] = 1;
  };
  IntegralCalculus(const IntegralCalculus& object);
  ~IntegralCalculus();
  inline void setLimits(double _lowerlimit, double _upperlimit);
  inline void setFunction(double(*_function)(double point));
  inline double getLimits();
  inline double getLeftLimit();
  inline double getRightLimit();
  inline void setAmountOfSubIntervals(int amount);
  double Calculation(int mode);
  IntegralCalculus& operator=(const IntegralCalculus& object);
  void outputResultValue();
};

IntegralCalculus::IntegralCalculus(const IntegralCalculus& object)
{
  function = object.function;
  result = object.result;
  amountOfSubIntervals = object.amountOfSubIntervals;
  limits = new double[2];
  limits[0] = object.limits[0];
  limits[1] = object.limits[1];
}

IntegralCalculus::~IntegralCalculus()
{
  delete[] limits;
}

void IntegralCalculus::setLimits(double _lowerlimit, double _upperlimit)
{
  bool flag = 1;
  while(flag)
  {
    flag = 0;
    try
    {
      if(_lowerlimit > _upperlimit)
        throw 1.0;
    }
    catch(const double error)
    {
      cout << "Lower limit more then upper limit" << endl;
      errorHandler(&_lowerlimit, &_upperlimit);
      if(_lowerlimit < _upperlimit)
      {
        limits[0] = _lowerlimit;
        limits[1] = _upperlimit;
      }
      else
        flag = 1;
    }
  }
  delete[] limits;
  limits = new double[2];
  limits[0] = _lowerlimit;
  limits[1] = _upperlimit;
}

void IntegralCalculus::setFunction(double(*_function)(double point))
{
  function = _function;
}

double IntegralCalculus::getLimits()
{
  return *limits;
}

double IntegralCalculus::getLeftLimit()
{
  return limits[0];
}

double IntegralCalculus::getRightLimit()
{
  return limits[1];
}

void IntegralCalculus::setAmountOfSubIntervals(int amount)
{
  amountOfSubIntervals = amount;
}

double IntegralCalculus::Calculation(int mode)
{
  double result = 0;
  switch(mode)
  {
    case 1:
    {
      result = leftRiemannSum();
      return result;
    }
    case 2:
    {
      result = middleRiemannSum();
      return result;
    }
    case 3:
    {
      result = rightRiemannSum();
      return result;
    }
    default:
    {
      return INT_MAX;
    }
  }
}

double IntegralCalculus::leftRiemannSum()
{
  double i = 0;
  double sum = 0;
  if(limits[0] == limits[1])
    return 0;
  double subIntervalValue = (limits[1] - limits[0]) / amountOfSubIntervals;
  for(i = limits[0]; i <= limits[1] - subIntervalValue; i += subIntervalValue)
  {
    result += function(i) * subIntervalValue;
  }
  return result;
}

double IntegralCalculus::middleRiemannSum()
{
  double i = 0;
  if(limits[0] == limits[1])
    return 0;
  if(limits[0] > limits[1])
  {
    cout << "ENTER PROPER LIMITS" << endl;
    return INT_MAX;
  }
  double subIntervalValue = (limits[1] - limits[0]) / amountOfSubIntervals;
  for (i = limits[0]; i <= limits[1] - subIntervalValue; i += subIntervalValue)
  {
    result += function(i + (subIntervalValue / 2)) * subIntervalValue;
  }
  return result;
}

double IntegralCalculus::rightRiemannSum()
{
  double i = 0;
  if(limits[0] == limits[1])
    return 0;
  if(limits[0] > limits[1])
  {
    cout << "ENTER PROPER LIMITS" << endl;
    return INT_MAX;
  }
  double subIntervalValue = (limits[1] - limits[0]) / amountOfSubIntervals;
  for (i = limits[0]; i <= limits[1] - subIntervalValue; i += subIntervalValue)
  {
    result += function(i + subIntervalValue) * subIntervalValue;
  }
  return result;
}

IntegralCalculus& IntegralCalculus::operator=(const IntegralCalculus& object)
{
  if(this == &object)
    return *this;
  function = object.function;
  result = object.result;
  amountOfSubIntervals = object.amountOfSubIntervals;
  limits[0] = object.limits[0];
  limits[1] = object.limits[1];
  return *this;
}

void IntegralCalculus::outputResultValue()
{
  cout << "Calculated value: " << result << endl;
}

void errorHandler(double* pointer)
{
  cout << "Enter proper values: " << endl;
  cout << "Enter lower limit: " << endl;
  cin >> pointer[0];
  cout << "Enter upper limit: " << endl;
  cin >> pointer[1];
}

void errorHandler(double* _lowerlimit, double* _upperlimit)
{
  cout << "Enter proper values: " << endl;
  cout << "Enter lower limit: " << endl;
  cin >> *_lowerlimit;
  cout << "Enter upper limit: " << endl;
  cin >> *_upperlimit;
}

int main()
{
  double* p;
  p = new double[2];
  p[0] = 12;
  p[1] = 2;
  IntegralCalculus object12(sin, 1000, p);
  object12.setLimits(8, 6);
  object12.Calculation(1);
  object12.outputResultValue();
  IntegralCalculus object1, object2, object3, object4, object5, object6, object7, object8, object9, object10;
  object1.setFunction(atan);
  object1.setAmountOfSubIntervals(1000);
  object1.setLimits(2, 12);
  object2.setFunction(sin);
  object2.setAmountOfSubIntervals(1000);
  object2.setLimits(4, 14);
  object3.setFunction(cos);
  object3.setAmountOfSubIntervals(1000);
  object3.setLimits(0, 4);
  object4.setFunction(exp);
  object4.setAmountOfSubIntervals(1000);
  object4.setLimits(8, 18);
  object5.setFunction(tan);
  object5.setAmountOfSubIntervals(1000);
  object5.setLimits(0, 10);
  object6.setFunction(asin);
  object6.setAmountOfSubIntervals(1000);
  object6.setLimits(0, 1);
  object7.setFunction(acos);
  object7.setAmountOfSubIntervals(1000);
  object7.setLimits(-1, 1);
  object8.setFunction(sinh);
  object8.setAmountOfSubIntervals(1000);
  object8.setLimits(16, 26);
  object9.setFunction(tanh);
  object9.setAmountOfSubIntervals(1000);
  object9.setLimits(18, 28);
  object10.setFunction(cosh);
  object10.setAmountOfSubIntervals(1000);
  object10.setLimits(20, 30);
  // pass as an arguments 1, 2, 3 for Left, Middle And Right Riemann Sum respectively.
  object1.Calculation(1);
  object1.outputResultValue();
  object2.Calculation(2);
  object2.outputResultValue();
  object3.Calculation(3);
  object3.outputResultValue();
  object4.Calculation(1);
  object4.outputResultValue();
  object5.Calculation(2);
  object5.outputResultValue();
  object6.Calculation(3);
  object6.outputResultValue();
  object7.Calculation(1);
  object7.outputResultValue();
  object8.Calculation(2);
  object8.outputResultValue();
  object9.Calculation(3);
  object9.outputResultValue();
  object10.Calculation(1);
  object10.outputResultValue();
  return 0;
}
