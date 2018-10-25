#include "misc.h"
#include <math.h>
#include <QVector>
#include <QString>
#include <QDebug>
#include <iostream>


// prototype
long double pow10(int n);


QVector<double> findBeautifulGrid(double min, double max, PlotWidget::AxisStyle as, int minTics)
{
	QVector<double> grid;
	double span=max-min;
	
	if(span<=0)
	{
		// for invalid span return empty grid
		//qDebug() << "findBeautifulGrid: invalid span";
		return grid;
	}
        
        if (as == PlotWidget::LOG) {
            double start = floor(log10(min));
            double end = ceil(log10(max));
            std::cout << "Start: " << start << "   End: " << end << std::endl;
            for (int e = start; e <= end; e++) {
                grid.append(pow(10, e));
            }
        }
        
        if (as == PlotWidget::LINEAR) {
	
            double step=span/minTics;
            double base=pow(10, floor(log10(step)));

            double normStep=step/base;

            if(normStep<2)
            {
                    step=base;
            }
            else if(normStep<5)
            {
                    step=2*base;
            }
            else
            {
                    step=5*base;
            }


            double tic=floor(min/step)*step;
            while(tic<=max)
            {
                    if(tic>=min)
                    {
                            if(fabs(tic)<step/100)
                                    tic=0;				// workaround for '0'

                            else if(fabs(tic-1.0)<step/100)
                                    tic=1.0;			// workaround for '1.0'

                            grid.append(tic);
                    }
                    tic+=step;
            }
        }
	return grid;
}


QString sciPrint(double value)
{

	int digits=7;
	QString output;

	int exp;				// 10 base of value
	int exp3;				// 1000 base of value

	int64_t rndValue;		// rounded value
	int64_t intValue;		// integer part of value
	int64_t fracValue;		// fractional part of value

	int intDigits;			// number of integer digits
	int fracDigits;			// number of fractional digits

	// find the 10 base and 1000 base of the value
	if(value!=0)
	{
		exp=(int)floor(log10(fabs(value)));
		exp3=(int)floor(log10(fabs(value))/3);
	}
	else
	{
		exp=0;
		exp3=0;
	}
	
	// do not break down numbers < 10^5
	if(exp>0 && exp<5)
	{
		exp3=0;
	}

	// transform the value to an integer format and round it
	rndValue=(int64_t)round(value*pow10(digits-1-exp));

	// get number of integer digits
	intDigits=exp-3*exp3+1;

	// get the integer part of value
	intValue=rndValue/pow10(digits-intDigits);

	// print integer part
	output=QString::number(intValue);


	// get number of digits of fractional part
	fracDigits=digits-intDigits;

	// get fractional part of value
	fracValue=fabs(rndValue % (int64_t)pow10(fracDigits));

	if(intDigits<digits && fracValue!=0)
	{
		// we need some fractional digits
		output+=".";

		for(int64_t base=pow10(fracDigits-1); base>0; base/=10)
		{
			//qDebug() << "digit:" << (fracValue/base);
			output+=QString::number(fracValue/base);
			fracValue%=base;
			if(fracValue==0)	// break when all digits are zero
			{
				break;
			}
		}
	}
	
	if(exp3!=0)
	{
		output+="e" + QString::number(3*exp3);
	}
	
	return output;
}


long double pow10(int n)
{
	long double pow=1;
	if(n>0)
	{
		for(int i=0; i<n; i++)
		{
			pow*=10;
		}
	}
	else if(n<0)
	{
		n=-n;
		for(int i=0; i<n; i++)
		{
			pow/=10;
		}
	}
	return pow;
}
