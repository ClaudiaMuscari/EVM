// Use trilinear interpolation using nearest cell center and cell-center
// gradient information.
velocity = U_[cellID];
velocity+= rFromShaft[cellID]*alignedVector1*rotOmega;
vector versor=velocity/mag(velocity);
EVMSampDir=(alignedVector2^versor);
EVMSampDir/=mag(EVMSampDir); 
scalar EVMInt=EVMlength/(numEVMPoints-1);
int  i=0;  //valid if just one turbine
for (int m = 0; m < numEVMPoints; m++)
{  
    EVMPoint=point-EVMdist*meshDim*versor+(EVMlength/2-EVMInt*m)*meshDim*EVMSampDir;   
    labelList localCellId(Pstream::nProcs(),0);
    localCellId[Pstream::myProcNo()] = mesh.findCell(YOUR_POINT);
    reduce(localCellId, maxOp<labeList>());
    EVMCellID=

}	 