// var salutations = document.forms["registration-form"]["salutations"].value.trim();
// var participantName = document.forms["registration-form"]["participantName"].value.trim();
// var username = document.forms["registration-form"]["username"].value.trim();
// var password = document.forms["registration-form"]["password"].value.trim();
// var email = document.forms["registration-form"]["email"].value.trim();
// var dob = document.forms["registration-form"]["dob"].value;
// var languagesKnown = document.querySelectorAll('input[name="languagesKnown"]:checked').length;
// var errorsFound = false;

var salutations = document.forms["registration-form"]["salutations"];
var participantName = document.forms["registration-form"]["participantName"];
var username = document.forms["registration-form"]["username"];
var password = document.forms["registration-form"]["password"];
var email = document.forms["registration-form"]["email"];
var dob = document.forms["registration-form"]["dob"];
var errorsFound = false;
var submit=false;
function updateValidationStatus(inputElem, isValid) {
    if (isValid) {
      inputElem.classList.add("valid");
      inputElem.classList.remove("invalid");
    } else {
      inputElem.classList.add("invalid");
      inputElem.classList.remove("valid");
    }
  }
  
  participantName.addEventListener("input", () => {
    updateValidationStatus(participantName, validateName());
  });
  
  username.addEventListener("input", () => {
    updateValidationStatus(username, validateUname());
  });
  
password.addEventListener("input", () => {
    updateValidationStatus(password, validatePwd());
});
email.addEventListener("input", () => {
    updateValidationStatus(email, validateMail());
});
// dob.addEventListener("input", () => {
//     updateValidationStatus(dob, validateDOB());
// });

function validateName() {
    const name = participantName.value.trim();
    const nameError = document.getElementById("name-error");
    var isValid=false;
    if (name === "") 
        nameError.textContent = submit?"Name is required":"";
    else if (!/^[A-Za-z]{1,2}\s[A-Za-z]+(\s([A-Za-z]+))?$/.test(name))
        nameError.innerHTML = submit?"Invalid name format":"";
    else
    {
        nameError.innerHTML = "";
        isValid=true;
    }
    if(!isValid && !errorsFound)
    {
        participantName.focus();
        nameError.innerHTML = submit?"Invalid name format":"";
        participantName.value="";
        errorsFound=true;
    }
    return isValid;
}

function validateUname() {
    const uname = username.value.trim();
    const uError = document.getElementById("username-error");
    var isValid=false;
    if (uname === "") 
        uError.textContent = submit?"Username is required":"";
    else if (!/^[A-Za-z]+$/.test(uname))
        uError.innerHTML = submit?"Invalid username format":"";
    else
    {
        uError.innerHTML = "";
        isValid=true;
    }
    if(!isValid && !errorsFound)
    {
        username.focus();
        uError.innerHTML = submit?"Invalid username format":"";
        username.value="";
        errorsFound=true;
    }
    return isValid;
}
function validatePwd() {
    const pwd = password.value.trim();
    const pwdError = document.getElementById("password-error");
    var isValid=false;
    if (pwd === "") 
        pwdError.textContent = submit?"Password is required":"";
    else if (!/(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*()_+}{":;?/><.,])(?=.{8,})/.test(pwd))
        pwdError.innerHTML = submit?"Invalid password format":"";
    else
    {
        pwdError.innerHTML = "";
        isValid=true;
    }
    if(!isValid && !errorsFound)
    {
        password.focus();
        pwdError.innerHTML = submit?"Invalid password format":"";
        password.value="";
        errorsFound=true;
    }
    return isValid;
}
function validateMail() {
    const mail = email.value.trim();
    const mailError = document.getElementById("email-error");
    var isValid=false;
    if (mail === "") 
        mailError.textContent = submit?"Mail is required":"";
    else if (!/^[\w-\.]+@(?:[\w]+\.)+[\w]{2,4}$/.test(mail))
        mailError.innerHTML = submit?"Invalid email format":"";
    else
    {
        mailError.innerHTML = "";
        isValid=true;
    }
    if(!isValid && !errorsFound)
    {
        email.focus();
        mailError.innerHTML = submit?"Invalid email format":"";
        email.value="";
        errorsFound=true;
    }
    return isValid;
}
// function validateDOB() {
//     const dobDate = new Date(dob.value.trim());
//     const today = new Date();
//     const dobError = document.getElementById("dob-error");
//     var isValid=true;
//     var age = today.getFullYear() - dobDate.getFullYear();
//     var monthDiff = today.getMonth() - dobDate.getMonth();
//     if (monthDiff < 0 || (monthDiff === 0 && today.getDate() < dobDate.getDate())) {
//       age--;
//     }
//     if (age < 18 || age > 35) {
//       dobError.innerHTML = "Invalid age";
//       isValid=false;
//       if (!isValid && !errorsFound) {
//             dob.focus();
//             errorsFound = true;
//         }
//     }
//     return isValid;    
// }

const checkboxes = document.querySelectorAll('input[type="checkbox"][name="languagesKnown"]');
const languagesKnownError = document.getElementById("languagesKnown-error");
for (const checkbox of checkboxes) {
    checkbox.addEventListener('change', () => {
        languagesKnownError.innerHTML=(!validateLanguages() && submit)?"Please select at least 2 languages":"";
    });
  }
  function validateLanguages()
{
    var languagesKnown = document.querySelectorAll('input[name="languagesKnown"]:checked').length;
    if (languagesKnown < 2) {
        if (!errorsFound) {
            document.forms["registration-form"]["languagesKnown"][0].focus();
            languagesKnownError.innerHTML=submit?"Please select at least 2 languages":"";
            errorsFound = true;
        }
        return false;
    }
    return true;
}
function showOtherLanguage() {
    var checkbox = document.getElementsByName("languagesKnown")[3];
    var input = document.getElementById("other-language");
    if (checkbox.checked) {
      input.style.display = "block";
      input.required = true;
    } else {
      input.style.display = "none";
      input.required = false;
    }
  }
  
function validateForm(event) {
    submit=true;
    errorsFound=false;
    if(!(!validateName()||!validateUname()||!validatePwd()||!validateMail()||!validateLanguages()))
    {
        alert("Details have been submitted Successfully");
        errorsFound=true;
        return true;
    }
    //submit=false;
    // event.preventDefault();
    return false;
}
  function clearForm() {
    document.getElementById("registration-form").reset();
    salutations[0].focus();
  }