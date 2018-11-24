var theSocket = new WebSocket("ws://"+location.hostname+":81", ['arduino']);

function sendJSON(theJSON)
{
  theSocket.send(JSON.stringify(theJSON));
}

theSocket.onmessage = function (event) {
  var msg=JSON.parse(event.data);
  switch(msg.type)
  {
	case "setText":
		document.getElementById(msg.id).innerHTML = msg.newText;		
	break;
	case "getText":
		sendJSON({type: "response", id: msg.id, subType: "getText", text: document.getElementById(msg.id).innerHTML});
		break;
	case "getProperty":
		sendJSON({type: "response", id: msg.id, subType: "getProperty", propertyName: msg.propertyName, value: document.getElementById(msg.id)[msg.propertyName]});
		break;
	case "evalAndTell"://this is probably ok... js is sandboxed anyway, I guess... #yolo
		sendJSON({type: "response", id:msg.id, subType:"evalAndTell", value: eval(msg.value)});
		break;
	case "setProperty":
		if(msg.value=="false")//do we want to do it like this actually?
		{
			msg.value=false;
		}
		if(msg.value=="true")//do we want to do it like this actually?
		{
			msg.value=true;
		}
		document.getElementById(msg.id)[msg.propertyName]=msg.value;
		break;
	default:
		console.log("got invalid request");
	break;

  }
}

function activateTab(theEvent, tabName) {
  var allTabContents = document.getElementsByClassName("tabContent");
  //iterate over tabs and hide them all
  for (var i = 0; i < allTabContents.length; i++) {
    allTabContents[i].style.display = "none";
  }
  //display the current one
  document.getElementById(tabName).style.display = "block";

  //set the currently clicked button to active
  var allTabLinks = document.getElementsByClassName("tabLink");
  for (i = 0; i < allTabLinks.length; i++) {
    allTabLinks[i].className = allTabLinks[i].className.replace(" active", "");
  }
  theEvent.currentTarget.className += " active";

}
