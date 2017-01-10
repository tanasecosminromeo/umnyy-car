var term;

function output(str){ term.output(str); }
  // Set the command-line prompt to include the user's IP Address
  //$('.prompt').html('[' + codehelper_ip["IP"] + '@HTML5] # ');
    $('.prompt').html('[tanase@Talks90] # ');

  // Initialize a new terminal object
  term = new Terminal('#input-line .cmdline', '#container output');
  term.init();
  
  // Update the clock every second
  setInterval(function() {
    function r(cls, deg) {
      $('.' + cls).attr('transform', 'rotate('+ deg +' 50 50)')
    }
    var d = new Date()
    r("sec", 6*d.getSeconds())  
    r("min", 6*d.getMinutes())
    r("hour", 30*(d.getHours()%12) + d.getMinutes()/2)
  }, 1000);
	
var socket;
	
if(!("WebSocket" in window)){
	$('#chatLog, input, button, #examples').fadeOut("fast");	
	$('<p>Oh no, you need a browser that supports WebSockets. How about <a href="http://www.google.com/chrome">Google Chrome</a>?</p>').appendTo('#container');		
} else {
	connect();
}

$("div.videomotion").append('<img src="http://'+document.location.hostname+':8081" />');

function connect(){
	
	try {
		socket = new WebSocket("ws://"+document.location.hostname+":8000");
		
		socket.onopen = function(){
			//output('<p class="event">Socket Status: '+socket.readyState+' (open)');	
		};
		
		socket.onmessage = function(msg){
			//output('<p class="message">Received: '+msg.data);					
		};
		
		socket.onclose = function(){
			//output('<p class="event">Socket Status: '+socket.readyState+' (Closed)');
		}	;		
		
	} catch(exception){
		output('<p>Error'+exception);
	}
	
	//socket.send(text);
	//socket.close();
	
}
