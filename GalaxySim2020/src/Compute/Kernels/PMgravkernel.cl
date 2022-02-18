#define G 4.300E-03f // (pc/solarMass) * (km/s)^2 
#define KM_PER_PARSEC 3.086E+13f

float calcWaveNumber (int ind, int dim);
// This kernel solves the poisson equation for each grid cell in fourier space. This gives you a 
// potential Del^2 Phi equal to 4 * pi * G * rho where rho is density. To slove for phi in fourier
// space all we need to do is multiply the other side by -1/ ((k_x)^2 + (k_y)^2 + (k_z)^2), where 
// k is the wave number in that diminsion. For a more in depth explaination, see
// https://observablehq.com/@rreusser/2d-n-body-gravity-with-poissons-equation by Ricky Reusser.
__kernel void calcDeltaPhi (__global const float* densityReal,
											__global const float* densityComplex,
											const int dimX, const int dimY, const int dimZ,
											const float dimOfCell,
											__global float* gradXReal, __global float* gradXComplex,
											__global float* gradYReal, __global float* gradYComplex,
											__global float* gradZReal, __global float* gradZComplex)
{
	int gid = get_global_id(0);
	int index = gid;
	int x, y, z;
	z = (index % dimZ);
	index = (index - z)/ dimZ;
	y = (index % dimY);
	index = (index - y) / dimY;
	x = index;
	float waveX, waveY, waveZ;
	
	waveZ	= calcWaveNumber(z+1,dimZ);
	waveY = calcWaveNumber(y+1,dimY);
	waveX = calcWaveNumber(x+1,dimX);
	
	float phiReal =    -(4 * M_PI_F * densityReal[gid]   )/ ((waveX * waveX) + (waveY * waveY) + (waveZ * waveZ));
	float phiComplex = -(4 * M_PI_F * densityComplex[gid]) / ((waveX * waveX) + (waveY * waveY) + (waveZ * waveZ));

	gradXReal[gid] = -waveX * phiComplex;
	gradXComplex[gid]    = waveX * phiReal;

	gradYReal[gid] = -waveY * phiComplex;
	gradYComplex[gid]    = waveY * phiReal;
										
	gradZReal[gid] = -waveZ * phiComplex;
	gradZComplex[gid]    = waveZ * phiReal;

	/*gradZComplex[gid] = waveZ;
	gradZReal[gid] =  waveY;*/
}


float calcWaveNumber (int ind, int n)
{
	int ndiv2plus1 = (int)floor ((float)n / 2) + 1;
	int waveNumberInd = ind > ndiv2plus1 ? -(n+2) + ind : ind;
	return (2 * M_PI_F) * (float)waveNumberInd / (float)n;
}