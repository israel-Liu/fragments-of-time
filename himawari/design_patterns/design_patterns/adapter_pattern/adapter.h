#include <iostream>

class Rect
{
public:
    double GetLength()
    {
        return length_;
    }

    void SetLength(double length)
    {
        length_ = length;
    }

    double GetWide()
    {
        return wide_;
    }

    void SetWide(double wide)
    {
        wide_ = wide;
    }

private:
    double length_ = 0.0;
    double wide_ = 0.0;
};

class Calculator
{
public:
    double GetArea(Rect& rect)
    {
        return rect.GetLength() * rect.GetWide();
    }
};

class Triangle
{
public:
    double GetBottom()
    {
        return bottom_;
    }

    double GetHigh()
    {
        return high_;
    }

private:
    double bottom_ = 0.0;
    double high_ = 0.0;
};

class CalculatorAdapter
{
public:
    //double GetArea(Triangle& triangle)
    //{
    //    Calculator* calculator = new Calculator();
    //    Rect* rect = new Rect();
    //    rect->SetLength = triangle.GetBottom();
    //    rect->SetWide = 0.5 * triangle.GetHigh();

    //    return calculator->GetArea(*rect);
    //}

    //double GetArea(Triangle& triangle)
    //{
    //    Calculator calculator;
    //    Rect rect;
    //    rect.SetLength = triangle.GetBottom();
    //    rect.SetWide = 0.5 * triangle.GetHigh();

    //    return calculator.GetArea(rect);
    //}

    double GetArea(Triangle& triangle)
    {
        rect_.SetLength = triangle.GetBottom();
        rect_.SetWide = 0.5 * triangle.GetHigh();

        return calculator_.GetArea(rect_);
    }

private:
    Calculator calculator_;
    Rect rect_;
};