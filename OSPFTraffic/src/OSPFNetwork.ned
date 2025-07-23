//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ospftraffic;

import ospftraffic.OSPFRouter;  // Import simple module definition

network OSPFNetwork
{
    parameters:
        @display("bgb=600,400");
        @display("bgb=677,488");
    submodules:
        r1: OSPFRouter {
            parameters:
                routerId = 1;
                @display("p=134,128");
        }
        r2: OSPFRouter {
            parameters:
                routerId = 2;
                @display("p=241,111");
        }
        r3: OSPFRouter {
            parameters:
                routerId = 3;
                @display("p=202,254");
        }
        r4: OSPFRouter {
            parameters:
                routerId = 4;
                @display("p=398,111");
        }
        r5: OSPFRouter {
            parameters:
                routerId = 5;
                @display("p=450,215");
        }
        r6: OSPFRouter {
            parameters:
                routerId = 6;
                @display("p=437,308");
        }
        r7: OSPFRouter {
            parameters:
                routerId = 7;
                @display("p=134,365");
        }

    connections:
        // Ring connections (r1 <-> r2 <-> r3 <-> r1)
        r1.out++ --> {  delay = 10ms; } --> r2.in++;
        r2.out++ --> {  delay = 10ms; } --> r3.in++;
        r3.out++ --> {  delay = 10ms; } --> r1.in++;

        r2.out++ --> {  delay = 10ms; } --> r1.in++;
        r3.out++ --> {  delay = 10ms; } --> r2.in++;
        r1.out++ --> {  delay = 10ms; } --> r3.in++;

        // Star connections (r3 center)
        r3.out++ --> {  delay = 10ms; } --> r4.in++;
        r3.out++ --> {  delay = 10ms; } --> r5.in++;
        r3.out++ --> {  delay = 10ms; } --> r6.in++;

        r4.out++ --> {  delay = 10ms; } --> r3.in++;
        r5.out++ --> {  delay = 10ms; } --> r3.in++;
        r6.out++ --> {  delay = 10ms; } --> r3.in++;

        r2.out++ --> {  delay = 10ms; } --> r4.in++;
        r4.out++ --> {  delay = 10ms; } --> r2.in++;

        r6.out++ --> {  delay = 10ms; } --> r7.in++;
        r7.out++ --> {  delay = 10ms; } --> r6.in++;

        r5.out++ --> {  delay = 10ms; } --> r7.in++;
        r7.out++ --> {  delay = 10ms; } --> r5.in++;

}
