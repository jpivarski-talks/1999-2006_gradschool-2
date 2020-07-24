      function fitfunc2(invm)
      common/pawpar/par(4)

      real invm,mn,mlsp,ep2
      real p,hold,mz
      real gnij,hold2,en,pole
      real ep1
      real hnew

      mz=91.1882
      mlsp=107.697
      mn=par(2)+mlsp
      ep1=1.0
      ep2=-1.0

      p=mn*mn*mn*mn
      p=p+mlsp*mlsp*mlsp*mlsp
      p=p+invm*invm*invm*invm
      p=p-2.0*mn*mn*invm*invm
      p=p-2.0*mn*mn*mlsp*mlsp
      p=p-2.0*invm*invm*mlsp*mlsp
      if(p.lt.0.0) then
         hold = 0.0
      else
         p=sqrt(p)/(2.0*mn)
      
         pole=(invm*invm-mz*mz)
      
         hold=mn*mn*mn*mn
         hold=hold+mlsp*mlsp*mlsp*mlsp
         hold=hold+invm*invm*mlsp*mlsp
         hold=hold-2.0*invm*invm*invm*invm
         hold=hold+mn*mn*(invm*invm-2.0*mlsp*mlsp)
         hold=hold+6.0*ep1*ep2*invm*invm*mn*mlsp
      
         hold=hold*invm*p
         hold=hold/(mlsp*mlsp*pole*pole)
      endif

      mn=par(4)+mlsp
      ep1=1.0
      ep2=1.0

      p=mn*mn*mn*mn
      p=p+mlsp*mlsp*mlsp*mlsp
      p=p+invm*invm*invm*invm
      p=p-2.0*mn*mn*invm*invm
      p=p-2.0*mn*mn*mlsp*mlsp
      p=p-2.0*invm*invm*mlsp*mlsp
      if(p.lt.0.0) then
         hnew = 0.0
      else
         p=sqrt(p)/(2.0*mn)
      
         pole=(invm*invm-mz*mz)
      
         hnew=mn*mn*mn*mn
         hnew=hnew+mlsp*mlsp*mlsp*mlsp
         hnew=hnew+invm*invm*mlsp*mlsp
         hnew=hnew-2.0*invm*invm*invm*invm
         hnew=hnew+mn*mn*(invm*invm-2.0*mlsp*mlsp)
         hnew=hnew+6.0*ep1*ep2*invm*invm*mn*mlsp
      
         hnew=hnew*invm*p
         hnew=hnew/(mlsp*mlsp*pole*pole)
      endif
      
      fitfunc2=(par(1)*hold)+(par(3)*hnew)
      return 
      end
