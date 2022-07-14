import Pie from "./pieViz.js";
import eleD from "./ElecData.js";
import usageD from "./UsageData.js";
class Data {
     constructor(){
          this.onT=Pie[0];
          this.offT=Pie[1];
          this.EleD=[['wh', 'period']];
          this.UsageD=[['Activation-Time', 'Day']];
          this.SavingsD=[['Month', 'Savings in wH','Temperature(Avg)']];
     }
}