#include "MLProblem.h"
#include <string>
#include "../../Interface/ISolver.h"

//************************************************************************************************
 MLProblem::MLProblem()
 {
   det_cost=NULL;
 };
//************************************************************************************************
 MLProblem::MLProblem(const MLProblem& x)
 {
  *this=x;
 };
//************************************************************************************************
 void MLProblem::operator = (const MLProblem& x)
 {
   FMachineLine=x.FMachineLine;
   FRMachineLine=x.FRMachineLine;
   _MaxBufferSumm = x._MaxBufferSumm;
   if(det_cost)delete[] det_cost;
   det_cost =new double[GetSize()];
   for(int i=0;i<GetSize();i++)
    det_cost[i]=x.det_cost[i];
   inv_coef=x.inv_coef;
 }
//************************************************************************************************
 MLProblem::~MLProblem()
 {
   FreeMemory();
 }
//************************************************************************************************
 void MLProblem::FreeMemory()
 {
   FMachineLine.FreeMemory();
   FRMachineLine.FreeMemory();
   if(det_cost)delete[] det_cost;
  };
//************************************************************************************************
 int MLProblem::MachineQuantity() const
 {
   return FMachineLine.WorkStationQuantity();
 };
//************************************************************************************************
 void MLProblem::SetMachineQuantity(int x)
 {
   FMachineLine.SetWorkStationQuantity(x);
   FRMachineLine.SetWorkStationQuantity(x);
 };
//************************************************************************************************
 int MLProblem::BufferQuantity() const
 {
   return FMachineLine.BufferQuantity();
 };
//************************************************************************************************
 void MLProblem::SetBufferQuantity(int x)
 {
   FMachineLine.SetBufferQuantity(x);
   FRMachineLine.SetBufferQuantity(x);
   det_cost= new double[x];
   for(int i=0;i<x;i++)det_cost[i]=0;
 };
//************************************************************************************************
 long MLProblem::MaxBufferSumm()
 {
	 return _MaxBufferSumm;
 };
//************************************************************************************************
 int MLProblem::GetSize() const
 {
   return FMachineLine.BufferQuantity()-2;
 };
//************************************************************************************************
 void MLProblem::Parallel(Machine* mp1,Machine* mp2)
 {
     double pl=mp1->C/(1+mp1->Lambda/mp1->Mu)+mp2->C/(1+mp2->Lambda/mp2->Mu);
     mp1->C=mp1->C+mp2->C;
     mp1->Lambda=mp1->Lambda*mp2->Mu/(mp2->Lambda+mp2->Mu)+mp2->Lambda*mp1->Mu/(mp1->Mu+mp1->Lambda);
     mp1->Mu=mp1->Lambda/(mp1->C/pl-1);
 };
//************************************************************************************************
 void MLProblem::Series(Machine* mp1,Machine* mp2,double& hr,double& avg_stockr)
 {

  double k,am,fi1,
         fi2,mindb,
         pr,lamp,mup,
         lama,mua,dbp,
         dba,prp,pra,
         lmp,lma,mp,ma,
         dp,da,rp,ra;

  lam1 = mp1->Lambda;
  mu1 = mp1->Mu;
  deb1 = mp1->C;

  lam2 = mp2->Lambda;
  mu2 = mp2->Mu;
  deb2 = mp2->C;

  h = hr;
  avg_stock = avg_stockr;

  f11x0=0;
  f11xh=0;
  f10x0=0;
  f10xh=0;
  f01x0=0;
  f01xh=0;
  f00x0=0;
  f00xh=0;

  F11x0=0;
  F11xh=0;
  F10x0=0;
  F10xh=0;
  F01x0=0;
  F01xh=0;
  F00x0=0;
  F00xh=0;

  P11x0=0;
  P11xh=0;
  P10xh=0;
  P01x0=0;

  I1=lam1/mu1;
  I2=lam2/mu2;

  if(fabs(deb1-deb2)<=eps)
   if(fabs(I1-I2)<=eps)
   {
    func0(k);
    avg_stock=h*h*k*(2+(mu1+mu2)/(lam1+lam2)+(lam1+lam2)/(mu1+mu2))/2+h*(P11xh+P10xh);
   }
   else
   {
    func1(am,k);
    avg_stock=fi(am)*k*(2+(mu1+mu2)/(lam1+lam2)+(lam1+lam2)/(mu1+mu2))+h*(P11xh+P10xh);
   }
  else
  {
   func2(k);
   if(deb1>deb2)
   {
    fi1=fi(a1);
    fi2=fi(a2);
    avg_stock=k*(1+deb1/(deb2-deb1)+lam1/(mu1+mu2))*(fi1-fi2);
    avg_stock=avg_stock+k*(1-deb2/(deb2-deb1)+lam2/(mu1+mu2))*((a1-A)*fi1-(a2-A)*fi2)/B;
    avg_stock=avg_stock+h*(P11xh+P10xh);
   }
   else avg_stock=k*(1+deb1/(deb2-deb1)+lam1/(mu1+mu2))*(fi(a1)-(a1-A)/(a2-A)*ex(h*(a1-a2))*fi(a2))+
                 k*(1-deb2/(deb2-deb1)+lam2/(mu1+mu2))*
                 ((a1-A)*fi(a1)-(a1-A)*fi(a2)*ex(h*(a1-a2)))/B+
                 h*P10xh;
  }
  if(deb1>deb2)mindb=deb2;
  else mindb=deb1;

  pr=(F11xh+F01xh+P11xh)*deb2+P11x0*mindb;

  if(deb1>=deb2)
  {
   lamp=lam2+(deb2*f01x0+lam1*P11x0)/(F11xh+F01xh+P11xh+P11x0);
   mup=(mu1*P01x0+mu2*(F00xh+F10xh+P10xh))/(F00xh+F10xh+P01x0+P10xh);
  }
  else
  {
   lamp=lam2+(P11x0*deb1*(1+lam1/deb2)+f01x0*deb2+f11x0*(deb2-deb1))/
        	(F11xh+F01xh+deb1/deb2*P11x0);
   mup=(mu2*(F10xh+F00xh+P10xh)+mu1*P01x0+deb1*P11x0)/
            (F10xh+F00xh+P10xh+P01x0+P11x0*(1-deb1/deb2));
  };

  if(deb1<=deb2)
  {
   lama=lam1+(deb1*f10xh+lam2*P11xh)/(F10xh+F11xh+P11x0+P11xh);
   mua=(mu1*(F01xh+F00xh+P01x0)+mu2*P10xh)/(F00xh+F01xh+P01x0+P10xh);
  }
  else
  {
   lama=lam1+(P11xh*deb2*(1+lam2/deb1)+f10xh*deb1+f11xh*(deb1-deb2))/
     (F11xh+F10xh+deb2/deb1*P11xh);
   mua=(mu1*(F00xh+F01xh+P01x0)+mu2*P10xh+deb2*P11xh)/
      (F00xh+F01xh+P01x0+P10xh+(1-deb2/deb1)*P11xh);
  };
  dbp=deb2;  dba=deb1;
  prp=dbp/(1+lamp/mup);
  pra=dba/(1+lama/mua);

  if(deb1==deb2)
  {
   lmp=lamp;  lma=lama; mp=mup;
   ma=mua; dp=dbp; da=dba;
  }
  else
   if(deb1>deb2)
   {
    dp=deb2;
    lmp=lam2+P01x0*mu1/(F11xh+F01xh+P11xh);
    mp=((F10xh+F00xh+P10xh)*mu2+P01x0*mu1)/(F10xh+F00xh+P10xh+P01x0);
    da=(deb1*(F11xh+F10xh)+deb2*P11xh)/(F11xh+F10xh+P11xh);
    lma=(lam1*(F11xh+F10xh+P11xh*deb2/deb1)+mu2*P10xh)/(F11xh+F10xh+P11xh);
    ma=(mu1*(F01xh+F00xh+P01x0)+P10xh*mu2)/(F01xh+F00xh+P10xh+P01x0);
   }
   else
   {
    da=deb1;
    lma=lam1+P10xh*mu2/(F11xh+F10xh+P11x0);
    ma=((F01xh+F00xh+P01x0)*mu1+P10xh*mu2)/(F01xh+F00xh+P10xh+P01x0);
    dp=(deb2*(F11xh+F01xh)+deb1*P11x0)/(F11xh+F01xh+P11x0);
    lmp=(lam2*(F11xh+F01xh+P11x0*deb1/deb2)+mu1*P01x0)/(F11xh+F01xh+P11x0);
    mp=(mu2*(F10xh+F00xh+P10xh)+P01x0*mu1)/(F10xh+F00xh+P10xh+P01x0);
   };

  rp=dp/(1+lmp/mp);
  ra=da/(1+lma/ma);

  if(deb1<deb2)
  {
   lam1=lma;
   mu1=ma;
   deb1=da;
  }
  else
  {
   lam1=lmp;
   mu1=mp;
   deb1=dp;
  };

  mp1->Lambda=lam1;
  mp1->Mu=mu1;
  mp1->C=deb1;

  mp2->Lambda=lam2;
  mp2->Mu=mu2;
  mp2->C=deb2;

  hr=h;
  avg_stockr=avg_stock;

 };
//************************************************************************************************
 double MLProblem::ex(double y)
 {
  if( fabs(y) > 88 )
	  y=floor(y/fabs(y))*88;
  return exp(y);
 };
//************************************************************************************************
 void MLProblem::func0(double& k)
 {
  double c0=1/(deb1*(lam1+lam2)/(lam1*lam2)*(1+2*I1)+((1+I1)*(1+I1))/I1*h);
  f01x0=c0;  f01xh=c0;
  f10xh=f01xh; f10x0=f01x0;
  f00x0=I1*f01x0;f00xh=f00x0;
  f11x0=c0/I1; f11xh=f11x0;
  P11x0=deb1/lam2*f10x0;
  P11xh=deb1/lam1*f01xh;
  P01x0=deb1*(lam1+lam2)/(mu1*lam2)*c0;
  P10xh=deb1*(lam1+lam2)/(mu2*lam1)*c0;
  F01xh=c0*h;
  F10xh=F01xh;
  F11xh=c0*h/I1;
  F00xh=I1*c0*h;
  k=c0;
 };
//************************************************************************************************
 void MLProblem::func1(double& am,double& k)
 {
  double c;
  am=(lam2*mu1-lam1*mu2)/deb1*(lam1+lam2+mu1+mu2)/((lam1+lam2)*(mu1+mu2));
  c=1/(deb1*(lam1+lam2)/(lam2*mu1-lam1*mu2)*((1+I2)/I1*ex(am*h)-(1+I1)/I2));
  f01x0=c; f10x0=f01x0;
  f10xh=c*ex(am*h); f01xh=f10xh;
  f11x0=(mu1+mu2)/(lam1+lam2)*c; f11xh=f11x0*ex(am*h);
  f00x0=(lam1+lam2)/(mu1+mu2)*c; f00xh=f00x0*ex(am*h);
  P11x0=(deb1/lam2)*c;
  P11xh=(deb1/lam1)*f10xh;
  P01x0=deb1*(lam1+lam2)/(mu1*lam2)*c;
  P10xh=deb1*(lam1+lam2)/(lam1*mu2)*f10xh;
  F01xh=c*(ex(am*h)-1)/am;
  F10xh=F01xh;
  F11xh=(mu1+mu2)/(lam1+lam2)*F01xh;
  F00xh=(lam1+lam2)/(mu1+mu2)*F01xh;
  k=c;
 };
//************************************************************************************************
 double MLProblem::fufm01(double x)
 {
  if(deb1>deb2) return (w*(a1-A)*ex(a1*x)-w*(a2-A)*ex(a2*x))/B;
  else return (w*(a1-A)*ex(a1*x-h*(a1-a2))-w*(a1-A)*ex(a2*x))*ex(h*(a1-a2))/B;
 };
//************************************************************************************************
 double MLProblem::fufm10(double x)
 {
  if(deb1>deb2) return w*ex(a1*x)-w*ex(a2*x);
  else return w*ex(h*(a1-a2))*(ex(a1*x-h*(a1-a2))*(a2-A)-(a1-A)*ex(a2*x))/(a2-A);
 };
//************************************************************************************************
 double MLProblem::loif01(double x)
 {
  if(fabs(a2)!=0)
   if(deb1>deb2) return (w*(a1-A)/a1*(ex(a1*x)-1)-w*(a2-A)/a2*(ex(a2*x)-1))/B;
   else return (a1-A)*(w/a1*(ex(a1*x-h*(a1-a2))-ex(-h*(a1-a2)))-w/a2*(ex(a2*x)-1))/B*ex(h*(a1-a2));
  else
   if(deb1>deb2) return w*(a1-A)/(B*a1)*(ex(a1*x)-1)+w*A/B*x;
   else return w*(a1-A)/(B*a1)*(ex(a1*x)-1)-w*(a1-A)/B*ex(a1*h)*x;
 }
//************************************************************************************************
 double MLProblem::loif10(double x)
 {
  if(fabs(a2)!=0)
   if(deb1<deb2) return (w/a1*(a2-A)*(ex(a1*x-h*(a1-a2))-ex(-h*(a1-a2)))-w*(a1-A)/a2*(ex(a2*x)-1))*ex(h*(a1-a2))/(a2-A);
   else return w*(ex(a1*x)-1)/a1-w*(ex(a2*x)-1)/a2;
  else
   if(deb1>deb2) return w/a1*(ex(a1*x)-1)-w*x;
   else return w/a1*(ex(a1*x)-1)+w*(a1-A)/A*ex(a1*h)*x;
 }
//************************************************************************************************
 void MLProblem::func2(double& k)
 {
  double wm,mia;
  A=lam2/(deb2-deb1)-mu2*(mu1+mu2+lam1)/(deb1*(mu1+mu2));
  B=lam2/deb1*(mu1/(mu1+mu2)-deb2/(deb2-deb1));
  E=-lam1/deb2*(mu2/(mu1+mu2)+deb1/(deb2-deb1));
  D=lam1/(deb2-deb1)+mu1*(mu1+mu2+lam2)/(deb2*(mu1+mu2));
  di=(A-D)*(A-D)+4*E*B;
  a1=(A+D+sqrt(di))/2;
  a2=(A+D-sqrt(di))/2;

  if(fabs(a1)>fabs(a2))mia=fabs(a1);
  else mia=fabs(a2);

  if(mia*h<63)w=1;
  else if(mia*h<87) w=ex(-23);
    else if(mia*h<150) w=ex(-mia*h+63);
      else w=1.0E-30;

  f01x0=fufm01(0);
  f10xh=fufm10(h);

  if(deb1>deb2) f01xh=fufm01(h);
  else f01xh=0;
  if(deb2>deb1) f10x0=fufm10(0);
  else f10x0=0;

  f11x0=deb1/(deb2-deb1)*f10x0-deb2/(deb2-deb1)*f01x0;
  f11xh=deb1/(deb2-deb1)*f10xh-deb2/(deb2-deb1)*f01xh;
  f00xh=lam1/(mu1+mu2)*f10xh+lam2/(mu1+mu2)*f01xh;
  f00x0=lam1/(mu1+mu2)*f10x0+lam2/(mu1+mu2)*f01x0;
  P11xh=deb1/lam1*f01xh;
  P11x0=deb2/lam2*f10x0;
  P01x0=lam1/mu1*P11x0+deb2/mu1*f01x0;
  P10xh=deb1/mu2*f10xh+lam2/mu2*P11xh;
  F01xh=loif01(h);
  F10xh=loif10(h);
  F11xh=deb1/(deb2-deb1)*loif10(h)-deb2/(deb2-deb1)*loif01(h);
  F00xh=lam1/(mu1+mu2)*loif10(h)+lam2/(mu1+mu2)*loif01(h);
  wm=w;
  w=1/(F10xh+F01xh+F00xh+F11xh+P11xh+P10xh+P01x0+P11x0);
  f01x0=f01x0*w;
  f10xh=f10xh*w;
  f11x0=f11x0*w;
  f11xh=f11xh*w;
  f10x0=f10x0*w;
  f01xh=f01xh*w;
  P11xh=P11xh*w;
  P11x0=P11x0*w;
  P01x0=P01x0*w;
  P10xh=P10xh*w;
  F11xh=F11xh*w;
  F00xh=F00xh*w;
  F01xh=F01xh*w;
  F10xh=F10xh*w;
  k=w*wm;
 }
//************************************************************************************************
 double MLProblem::fi(double a)
 {
  double ah;
  ah=a*h;
  return (ex(ah)*(ah-1)+1)/(a*a);
 }
//************************************************************************************************
 int MLProblem::R1()
 {
  int minindex=0;
  double minsize=FMachineLine.getBuffer(0)->Volume;

  for(int i=1;i<BufferQuantity();i++)
  {
   if  (FMachineLine.ConsideredBuffer(i) &&
        FMachineLine.getBuffer(i)->Volume <= minsize &&
        FMachineLine.getBuffer(i)->PutingDetailMachineQuantity == 1 &&
	     FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->PutingDetailMachineNumber(0))->MachineNumber==1 &&
        FMachineLine.getBuffer(i)->TakingDetailMachineQuantity == 1 &&
	     FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(0))->MachineNumber==1
		)
   {
    minsize=FMachineLine.getBuffer(i)->Volume;
    minindex=i;
   }
  }
  return minindex;
 };
//************************************************************************************************
 void MLProblem::ReduceLine(Machine* mp1,double& stock_cost,double& inv_coef)
 {
  double avg_stock=0;
  stock_cost=0;
  //int qwe = 4; 
  while(true)
  {
   //qwe--;
   int ihm = R1();
   //ihm = qwe;
   //cout<<FMachineLine<<endl;
   //cout<<"Buffer number choose: "<<ihm+1<<endl;
   if( ihm != 0 )
   {
    double Volume=FMachineLine.getBuffer(ihm)->Volume;

    Series(FMachineLine.getWorkStation(FMachineLine.getBuffer(ihm)->PutingDetailMachineNumber(0)),
           FMachineLine.getWorkStation(FMachineLine.getBuffer(ihm)->TakingDetailMachineNumber(0)),
		   Volume,avg_stock);

	*mp1=*FMachineLine.getWorkStation(FMachineLine.getBuffer(ihm)->PutingDetailMachineNumber(0));

    stock_cost+=avg_stock*inv_coef*det_cost[ihm];

    FMachineLine.getWorkStation(FMachineLine.getBuffer(ihm)->PutingDetailMachineNumber(0))->TakingDetailBufferNumber=
    FMachineLine.getWorkStation(FMachineLine.getBuffer(ihm)->TakingDetailMachineNumber(0))->TakingDetailBufferNumber;

    int after_ihm=FMachineLine.getWorkStation(
	                    FMachineLine.getBuffer(ihm)->TakingDetailMachineNumber(0)
                      )->TakingDetailBufferNumber;

	int ind=FMachineLine.getWorkStation(
		                FMachineLine.getBuffer(ihm)->TakingDetailMachineNumber(0)
				)->TakingDetailBufferListNumber;

    FMachineLine.getBuffer(after_ihm)->PutingDetailMachineNumber(ind)=FMachineLine.getBuffer(ihm)->PutingDetailMachineNumber(0);

    FMachineLine.ConsideredBuffer(ihm)=false;
    FMachineLine.ConsideredWorkStationQuantity--;
    FMachineLine.ConsideredBufferQuantity--;

   }
   else
   {
    if(FMachineLine.ConsideredWorkStationQuantity == 1 &&
       FMachineLine.ConsideredBufferQuantity == 2 &&
       FMachineLine.getWorkStation(0)->MachineNumber==1)break;

    int i=-1;
	int j,k;
    bool b=true;
    while (i<FMachineLine.BufferQuantity()-1 && b==true)
    {
     i++;
     if(FMachineLine.ConsideredBuffer(i)==true)
     {
      if(FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(0))->MachineNumber>1)
      {
  					Parallel(
					   FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(0)),
                       &FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(0))->HelpMachine
			       );

	            *mp1=*FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(0));

				FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(0))->MachineNumber--;

				b=false;

      }
      if(FMachineLine.getBuffer(i)->TakingDetailMachineQuantity >= 2)
      {
       j=-1;
       while (j<FMachineLine.getBuffer(i)->TakingDetailMachineQuantity-1 && b==true)
       {
        j++;
        k=j;
        while (k<FMachineLine.getBuffer(i)->TakingDetailMachineQuantity-1 && b==true)
        {
         k++;
         if(FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(j))->TakingDetailBufferNumber ==
            FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k))->TakingDetailBufferNumber)
         {
  					Parallel(
					  FMachineLine.getWorkStation(
			                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(j)
				                              ),
                  FMachineLine.getWorkStation(
			                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
				                              )
			      );

	            *mp1=*FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(j));

			   FMachineLine.ConsideredWorkStationQuantity--;

			   FMachineLine.getBuffer(i)->TakingDetailMachineQuantity--;

			   int f_in=FMachineLine.getBuffer(i)->TakingDetailMachineQuantity;

               FMachineLine.getBuffer(
                FMachineLine.getWorkStation(
                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
                                        )->TakingDetailBufferNumber
                                  )->PutingDetailMachineQuantity--;

			   int s_in=FMachineLine.getBuffer(
                FMachineLine.getWorkStation(
                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
                                        )->TakingDetailBufferNumber
                                  )->PutingDetailMachineQuantity;

				int t=FMachineLine.getWorkStation(FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k))->TakingDetailBufferListNumber;
				if(s_in!=t)
				{
					int tt=FMachineLine.getBuffer(
                FMachineLine.getWorkStation(
                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
                                        )->TakingDetailBufferNumber
											)->PutingDetailMachineNumber(s_in);
FMachineLine.getBuffer(
                FMachineLine.getWorkStation(
                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
                                        )->TakingDetailBufferNumber
											)->PutingDetailMachineNumber(s_in)=
FMachineLine.getBuffer(
                FMachineLine.getWorkStation(
                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
                                        )->TakingDetailBufferNumber
											)->PutingDetailMachineNumber(t);
FMachineLine.getBuffer(
                FMachineLine.getWorkStation(
                 FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)
                                        )->TakingDetailBufferNumber
											)->PutingDetailMachineNumber(t)=tt;
										FMachineLine.getWorkStation(tt)->TakingDetailBufferListNumber=t;
				}

				if(f_in!=k)
				{
					t=FMachineLine.getBuffer(i)->TakingDetailMachineNumber(f_in);
					FMachineLine.getBuffer(i)->TakingDetailMachineNumber(f_in)=FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k);
					FMachineLine.getBuffer(i)->TakingDetailMachineNumber(k)=t;
					FMachineLine.getWorkStation(t)->GivingDetailBufferListNumber=k;
				}

               b=false;
         }
        };
       };
      };
     };
    };
   };
  };
 };
//************************************************************************************************
SolverResult MLProblem::eSolve(void*x_,...)
 {

  void** hx= &x_;
  long* x = (long*)(hx[0]);
  double* Debit = (double*)(hx[1]);
  double* AverageStock = (double*)(hx[2]);

  for(int i=0;i<GetSize();i++)
   FMachineLine.getBuffer(i+1)->Volume=x[i];

  GetParameterFromReduceLine(GetSize(),*Debit,*AverageStock);
  return SolutionFound;
 };
//************************************************************************************************
 void MLProblem::GetParameterFromReduceLine(int s,double& Debit,double& AverageStock)
 {
  long BufferSumm=0;
  for(int i=1;i<s;i++)
   BufferSumm+=FMachineLine.getBuffer(i)->Volume;

  Machine p;
  p.Lambda=1;
  p.Mu=1;
  p.C=1;
  AverageStock=0;
  ReduceLine(&p,AverageStock,inv_coef);
  FMachineLine=FRMachineLine;
  Debit=p.C/(1+p.Lambda/p.Mu);
 };
//************************************************************************************************
 void MLProblem::Copy(const void* x)
 {
    MLProblem* y = (MLProblem*)(x);
    *this = *y;
 };
//************************************************************************************************
void MLProblem::Remove()
{
	FreeMemory();
}
//************************************************************************************************
void* MLProblem::Clone()const
{
   MLProblem* p = new MLProblem(*this);
   return p;
}
//************************************************************************************************
 ifstream & operator >>(ifstream& in , MLProblem& x)
 {
  string s;

  int np=0;
  while(true)
  {
		if(np==3)break;
		else if(in.eof()==true)abort();

        getline(in,s);

        if(s.find("MachineLineParameter")!=string::npos)
		{
			in>>x.FMachineLine;
			x._MaxBufferSumm = 0;
			for(int i=1;i<x.BufferQuantity()-1;i++)
				x._MaxBufferSumm += x.FMachineLine.getBuffer(i)->Volume;
				
			x.FRMachineLine=x.FMachineLine;
			np++;
			continue;
        }

		if(s.find("BufferDetailCosts")!=std::string::npos)
		{
			if(x.det_cost)delete[] x.det_cost;
			x.det_cost= new double[x.BufferQuantity()];
			for(int i=0;i<x.BufferQuantity();i++)
				in>>x.det_cost[i];
			np++;
			continue;
		}
		
		if(s.find("InventoryCostCoefficient")!=std::string::npos)
        {
	     in>>x.inv_coef;
	     np++;
         continue;
        }

  }
  return in;
 };
//************************************************************************************************
 ofstream & operator <<(ofstream & out , MLProblem & x)
 {
   out<<"MachineLineParameter"<<endl<<x.FMachineLine<<endl;
   out<<"BufferDetailCosts"<<endl;
   for(int i=0;i<x.BufferQuantity();i++) out<<x.det_cost[i]<<' ';
   out<<endl;
   out<<"InventoryCostCoefficient"<<endl<<x.inv_coef<<endl;
  return out;
 };
//************************************************************************************************
 ostream & operator <<(ostream & out , MLProblem & x)
 {
   out<<"MachineLineParameter"<<endl<<x.FMachineLine<<endl;
   out<<"BufferDetailCosts"<<endl;
   for(int i=0;i<x.BufferQuantity();i++) out<<x.det_cost[i]<<' ';
   out<<endl;
   out<<"InventoryCostCoefficient"<<endl<<x.inv_coef<<endl;
  return out;
 };
//************************************************************************************************

