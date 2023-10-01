/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var inputName=document.getElementById("name");
var drop=document.getElementById("drop");
inputName.addEventListener("keyup",fun);
function fun(){
    console.log("enetere");
    drop.innerHTML=""
    var search=inputName.value.trim();
    if(search.length<=0)
        return;
    var url="/autocomplete/ajax?val="+search;
    var xhttp,x;
    xhttp=new XMLHttpRequest();
    xhttp.onreadystatechange=function(){
        if(xhttp.readyState==4 && xhttp.status==200){
            x=this.responseText;
            console.log(x)
            console.log("hello world");
            drop.innerHTML=x;
        }
    };
    xhttp.open("GET",url,true);
    xhttp.send();
}