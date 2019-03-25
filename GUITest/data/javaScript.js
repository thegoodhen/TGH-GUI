var theSocket; 

function openSocket()
{
  theSocket = new WebSocket("ws://"+location.hostname+":81", ['arduino']);

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
      case "evalAndToss":
	eval(msg.value);
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
      case "showToast":
	{
	  showToast(msg.text, msg.toastType);
	}
	break;
      default:
	console.log("got invalid request");
	break;

    }
  }
}

function sendJSON(theJSON)
{
  theSocket.send(JSON.stringify(theJSON));
}


function activateTab(theEvent, tabName, tabbedPaneId) {
  var allTabContents = document.getElementsByClassName("tabContent");
  //iterate over tabs and hide them all
  for (var i = 0; i < allTabContents.length; i++) {
    if(allTabContents[i].dataset.tabbedPaneId==tabbedPaneId)
    {
      allTabContents[i].style.display = "none";//Only hide those in the current tabbedPane
    }
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

function plot(chartContainerID, lineID, val)
{
  //console.log("slepice");
  //
  setTimeout(function(){
  var chartDiv=document.getElementById(chartContainerID);
  chartDiv.theData.push(val);
  chartDiv.theChart.updateOptions({'file':chartDiv.theData});
  //var now = new Date().getTime();
  //while(new Date().getTime() < now + 500){ /* do nothing */ } 
  },0);
}

function initChart(divName)
{
  var data=[];
  var theDiv=document.getElementById(divName);
  var g = new Dygraph(theDiv, data,
      {
	drawPoints: true,
	showRoller: false,
	labels: ['Time', 'Data'] 
     });
  theDiv.theChart=g;
  theDiv.theData=data;

}

function showToast(message, messageType) {
  var x = document.getElementById("toast");
  x.innerHTML=message;
  x.className = messageType;
  setTimeout(function(){ x.className = x.className.replace(messageType, ""); }, 8500);
}
