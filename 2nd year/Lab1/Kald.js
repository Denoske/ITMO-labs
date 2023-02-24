let inputY = document.getElementById("inputY"),
    ErrorY = document.getElementById("ErrorY"),
    inputR = document.getElementById("inputR"),
    ErrorR = document.getElementById("ErrorR"),
    inputX = document.getElementById("inputX");

document.querySelector("#submit").onclick = function (event){
    ErrorY.innerText = null;
    ErrorR.innerText = null;
    event.preventDefault();
     let Y = inputY.value,
         R = inputR.value,
         X = inputX.value,
         valid = true,
         check_php = '',
         shot = false,
         request = new XMLHttpRequest();
        if (Y.length > 10 ) {
            if (Y > -3 && Y < 3) Y = (Math.floor(Y * 100) / 100);
            else ErrorY.innerText = "Слишком много цирф, ограничемся десятью?";
            valid = false;
        }

    if (R.length > 10 ) {
        if (R > 1 && R < 4) R = (Math.floor(R * 100) / 100);
        else ErrorR.innerText = "Слишком много цирф, ограничемся десятью?";
        valid = false;
    }
     const url = "Joks.php?inputY=" + Y + "&inputR=" + R + "&inputX=" + X;
     request.open('GET',url);
     request.setRequestHeader('Content-Type', 'application/x-www-form-url');
     request.addEventListener("readystatechange",() =>{
         if (request.readyState === 4 && request.status === 200){
             check_php = request.responseText;
             let array_php = check_php.split(",");
             console.log(array_php)
             const table = document.querySelector(".table");
             const thead = document.createElement('thead');
             const tr = document.createElement('tr');
             const fragment = document.createDocumentFragment();
             let index;
             for (index in array_php) {
                 const th = document.createElement('th');
                 th.innerText = array_php[index];
                 fragment.appendChild(th);
                 tr.appendChild(fragment);
                 thead.appendChild(tr);
             }
             table.appendChild(thead);
         }
     });
     request.send();
        if (Y === "" ) {
            ErrorY.innerText = "Не может быть пустым";
            valid = false;
        } else if (Y.length > 10 ) {
            if (Y>-3 && Y<3) Y= ( Math.floor(Y * 100) / 100 );
            else ErrorY.innerText = "Слишком много цирф, ограничемся десятью?";
            valid = false;
        } else if (Y.split(' ').length > 1 ){
            ErrorY.innerText = "Enter just one number";
            valid = false;
        } else if (isNumber(Y) === false){
            ErrorY.innerText = "Y Должен быть число";
            valid = false;
        }else if (Y >= 3 || Y <= -3) {
            ErrorY.innerText = "Y must been in between -3 and 3";
            valid = false;
        }


        if (R === "" ) {
            ErrorR.innerText = "Не может быть пустым";
            valid = false;
        }else if (R.length > 10 ) {
            if (R > 1 && R < 4) R = (Math.floor(R * 100) / 100);
            else ErrorR.innerText = "Слишком много цирф, ограничемся десятью?";
            valid = false;
        }else if (R.split(' ').length > 1 ){
            ErrorR.innerText = "Enter just one number";
            valid = false;
        }else if (isNumber(R) === false){
            ErrorR.innerText = "R Должен быть число";
            valid = false;
        }else if (R >= 4 || R <= 1) {
            ErrorR.innerText = "R must been in between 1 and 4";
            valid = false;
        }



         if (valid === true){
            if ((X <= 0) && (X>=-R) && (Y>=-R/2) && (Y<=0) ){
                shot = true;
             }else if ((X<=0) && (Y>=0) && (Y<=(X+R)/2)){
                shot = true;
            }else if ((X>=0) && (Y<=0) && (Y>=-Math.sqrt(R*R-X*X))){
                shot = true
            }
            if (shot === true){
                //alert("Popadanie");
            }else {
                //alert("Promah");
            }
         }
         function isNumber(num) {
             return parseFloat(num) === Number(num);
         }













}