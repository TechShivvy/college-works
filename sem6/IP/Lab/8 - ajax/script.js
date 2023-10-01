var input = document.getElementById("myInput");
var dropDownList = document.getElementById("autocomplete-list");


input.addEventListener("keyup", suggest);

function selectCountry(country) {
    document.getElementById("myInput").value=country;
    document.getElementById("autocomplete-list").style.display="none";
}

function suggest() {

    if(input.value.length==0) {
        document.getElementById("autocomplete-list").style.display="none";
        return;
    }

    console.log("hello world");
    
    dropDownList.innerHTML = "";
   
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "search?q=" + input.value, true);
    xhr.setRequestHeader("Content-type", "application/json");
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {

            document.getElementById("autocomplete-list").style.display="block";
            
            var countryNames = JSON.parse(xhr.responseText);

            countryNames.forEach(function (countryName) {
                item=document.createElement("DIV");
                item.innerHTML = "<strong>" + countryName.substr(0, input.value.length) + "</strong>";
                item.innerHTML += countryName.substr(input.value.length);
                item.setAttribute("onclick", "selectCountry('" + countryName + "')");
                dropDownList.appendChild(item);
            });
            }
        }
        xhr.send();
}
