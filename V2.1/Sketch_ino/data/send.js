function xmlD(c) {
  var xmL = new XMLHttpRequest();
  xmL.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      c(this.responseText);
    }
  };
  xmL.open("GET", "/raw/", true);
  xmL.send();
}

export default xmlD;
