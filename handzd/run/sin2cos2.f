      function sin2cos2(x)
      common/pawpar/par(5)

      sin2cos2 = par(1) + par(2)*sin(x) + par(3)*cos(x)
      sin2cos2 = sin2cos2 + par(4)*sin(2*x) + par(5)*cos(2*x)

      return
      end
