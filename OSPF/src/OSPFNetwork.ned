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
package ospf;

simple OSPFRouter
{
    gates:
        input in[];      // expandable
        output out[];
}


network OSPFNetwork
{
    @display("bgb=505,397");
    submodules:
        r1: OSPFRouter {
            @display("p=427,210");
        }
        r2: OSPFRouter {
            @display("p=102,320");
        }
        r3: OSPFRouter {
            @display("p=244,41");
        }
        r4: OSPFRouter;
        
    connections :
        r1.out++ --> {  delay = 10ms; } --> r2.in++;
        r2.out++ --> {  delay = 10ms; } --> r1.in++;

        r1.out++--> {  delay = 10ms; } --> r3.in++;
        r3.out++ --> {  delay = 10ms; } --> r1.in++;

        r2.out++ --> {  delay = 10ms; } --> r3.in++;
        r3.out++ --> {  delay = 10ms; } --> r2.in++;

        r2.out++ --> {  delay = 10ms; } --> r4.in++;
        r4.out++ --> {  delay = 10ms; } --> r2.in++;

        r3.out++ --> {  delay = 10ms; } --> r4.in++;
        r4.out++ --> {  delay = 10ms; } --> r3.in++;
}

