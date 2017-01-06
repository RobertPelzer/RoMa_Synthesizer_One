/**
 * \class Sinusoid
 *
 *
 * \brief Simple sinusoid handler class.
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/01 14:16:20 $
 *
 * Contact: von_coler@intelligent-noise-solutions.de
 *
 *
 */

#include "squarewave.h"

Squarewave::Squarewave(double f, double a, double p,  int fS)
{
    freq    = f;
    amp     = a;
    phi     = p;
    fs      = fS;
}

double Squarewave::getNextSample()
{

    /// This method gets the next sample of the squarewave.
    /// The amplitude is applied and the angle of the
    /// squarewave is increased, according to the sample rate.

    // get squarewave value
	double thisVal = 0.0;

	if (phi <= M_PI) {
		thisVal = 1.0;
	}

    // apply amplitude
    thisVal = thisVal*amp;

    // rotate to next step
    phi += 2.0*M_PI * freq * (1.0/fs);

    // wrap to 2 pi
    if(phi>=2*M_PI)
        phi=0;

    return thisVal;

}


double Squarewave::frequency()
{
    return freq;
}

double Squarewave::amplitude()
{
    return amp;
}

double Squarewave::phase()
{
    return phi;
}

void Squarewave::frequency(double f)
{
    freq = f;
}

void Squarewave::amplitude(double a)
{
    amp = a;
}

void Squarewave::phase(double p)
{
    phi = p;
}
