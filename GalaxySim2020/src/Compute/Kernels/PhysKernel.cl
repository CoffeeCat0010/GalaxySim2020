#define G 4.300E-03f // (pc/solarMass) * (km/s)^2 
#define KM_PER_PARSEC 3.086E+13f

__kernel void calcPos (__global const float3* positions,
											 __global const float* masses,
											 const float softeningFactor,
											 const float timeStep,
											 __global float3* velocities,
											 __global float3* result)
{
	int gid = get_global_id (0);
	float3 workStarPos = positions[gid];

	float3 workStarVelocity = velocities[gid];

	result[gid] = 0.f;
	size_t globalSize = get_global_size (0);
	float3 accelVec = 0;
	for ( size_t i = 0; i < globalSize; ++i )
	{
		float3 currStarPos = positions[i];
		float currStarMass = masses[i];
		// This is taken from the an equation decribed here: http://www.scholarpedia.org/article/N-body_simulations_(gravitational).
		// It is slightly modified to only calculate the acceleration vector instead of the force vector, since we only care about
		// the new position and not how much force is applied. This is done by simply not including the mass of the body that we are
		// currently adding that acceleration vector to. As stated in the article linked, the softening factor (i.e. epsilon) should
		// be choosen to reflect the distance at which we want to dull the acceleration so as to avoid infinities.
		float3 distVec = 0;
		distVec.x = workStarPos.x - currStarPos.x;
		distVec.y = workStarPos.y - currStarPos.y;
		distVec.z = workStarPos.z - currStarPos.z;

		float distSqr = (distVec.x * distVec.x +
										 distVec.y * distVec.y +
										 distVec.z * distVec.z);
		float epsilonSqr = softeningFactor * softeningFactor;

		float denominator = pow (sqrt (distSqr + epsilonSqr), 3);

		float numerator = G * currStarMass;

		// In opencl the first expression is implictly converted to a float3 type then multiplied by the distance vector;
		float accelMult = -(numerator / denominator);
		accelVec.x += accelMult * distVec.x;
		accelVec.y += accelMult * distVec.y;
		accelVec.z += accelMult * distVec.z;

	}
	float3 accelVecKM = 0;
	accelVecKM.x = accelVec.x / KM_PER_PARSEC;
	accelVecKM.y = accelVec.y / KM_PER_PARSEC;
	accelVecKM.z = accelVec.z / KM_PER_PARSEC;

	float3 newVelocity = workStarVelocity;
	newVelocity.x += (timeStep * accelVecKM.x);
	newVelocity.y += (timeStep * accelVecKM.y);
	newVelocity.z += (timeStep * accelVecKM.z);

	float3 resultPos = workStarPos;
	resultPos.x += (workStarVelocity.x * timeStep + 0.5f * accelVecKM.x * (timeStep * timeStep)) / KM_PER_PARSEC;
	resultPos.y += (workStarVelocity.y * timeStep + 0.5f * accelVecKM.y * (timeStep * timeStep)) / KM_PER_PARSEC;
	resultPos.z += (workStarVelocity.z * timeStep + 0.5f * accelVecKM.z * (timeStep * timeStep)) / KM_PER_PARSEC;

	result[gid] = resultPos;

	velocities[gid] = newVelocity;

}