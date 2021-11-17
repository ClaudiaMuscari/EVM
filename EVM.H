// Use trilinear interpolation using nearest cell center and cell-center
// gradient information.
velocity = U_[cellID];
velocity+= rFromShaft[cellID]*alignedVector1*rotOmega;
vector versor=velocity/mag(velocity);
EVMSampDir=(alignedVector2^versor);
EVMSampDir/=mag(EVMSampDir); 
scalar EVMInt=EVMlength/(numEVMPoints-1);
int  i=0;  //valid if just one turbine
vector velocityEVM =vector::zero;
int count=0;
for (int m = 0; m < numEVMPoints; m++)
{  
    EVMPoint=point-EVMdist*meshDim*versor+(EVMlength/2-EVMInt*m)*meshDim*EVMSampDir;   
    labelList localCellId(Pstream::nProcs(),0);
    localCellId[Pstream::myProcNo()] = mesh.findCell(EVMPoint);
    reduce(localCellId, maxOp<labelList>());
    EVMCellID= localCellId[Pstream::myProcNo()]
    velocityEVM+=U_[EVMCellID];
    count++;
}
Pstream::gather(count, sumOp<int>());
Pstream::scatter(count); 

if(count!= 0)
{
    Pstream::gather(velocityEVM,sumOp<vector>());
    Pstream::scatter(velocityEVM);
    velocityEVM=velocityEVM/count;
} 

velocity=velocityEVM;