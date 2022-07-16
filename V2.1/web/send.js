import wetherDF from "./draw.js";
function xmlD(c) {
  var xmL = new XMLHttpRequest();
  xmL.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      c(this.responseText);
    }
  };
  xmL.open("GET", "Data.xml", true);
  xmL.send();
}
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function () {
  if (this.readyState == 4 && this.status == 200) {
    console.log(this.responseText);
  }
};
xhttp.open("POST", "\ref", true);
xhttp.send(wetherDF[0]);
export default xmlD;
