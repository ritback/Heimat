
function closeAllArticles(){
    var accordionTitleButtons = document.getElementsByClassName("accordionTitleButton");

    let i;
    for (i = 0; i < accordionTitleButtons.length; i++) {
        // close other panels
        accordionTitleButtons[j].classList.add("panelNoTransition");
        accordionTitleButtons[i].style.minWidth = null;
        var panel  = accordionTitleButtons[i].nextElementSibling;
        panel.classList.add("panelNoTransition");
        panel.style.maxHeight = null;
    }
}




function scriptAfterFullLoad(){


var content = document.getElementById("content");  
content.addEventListener("click", function(){
    if (event.target === event.currentTarget) {
        closeAllArticles();
    }
});

    
    

let k;    
var panelBottomMargin = document.getElementsByClassName("panelBottomMargin");
for (k = 0; k < panelBottomMargin.length; k++) {
    panelBottomMargin[k].addEventListener("click", function(){
        if (event.target === event.currentTarget) {
            closeAllArticles();
        }
    });
}
    
    
    
let i, j;

var accordionTitleButtons = document.getElementsByClassName("accordionTitleButton");

for (i = 0; i < accordionTitleButtons.length; i++) {
    accordionTitleButtons[i].addEventListener("click", function(){
      
      // close other panels
        var otherPanel;
      for(j = 0; j < accordionTitleButtons.length; j++){
          // remove transition
          accordionTitleButtons[j].classList.add("panelNoTransition");
          otherPanel = accordionTitleButtons[j].nextElementSibling;
          otherPanel.classList.add("panelNoTransition");
          
          if (accordionTitleButtons[j] != this){   
            if (otherPanel.style.maxHeight) {
                //close panel
                accordionTitleButtons[j].style.minWidth = null;
                otherPanel.style.maxHeight = null;
                
            }
        }
      }
      // open / close the correct one.
      var panel = this.nextElementSibling;
      if (panel.style.maxHeight) {
          //close panel
            this.style.minWidth = null;
          panel.style.maxHeight = null;
      }
      else {
          
            // place the panel on top;
          this.scrollIntoView({behavior: "instant", block: "start"});
      
          var headOffset = document.getElementById("head").getBoundingClientRect().bottom;
          window.scrollBy(0, -headOffset);
      
          
          // add back transition
            this.classList.remove("panelNoTransition");
          panel.classList.remove("panelNoTransition"); 
          
          // resize
          this.style.minWidth = "100%";
          panel.style.maxHeight = panel.scrollHeight + "px";
          
          // resize the parent list;
          let newHeightList = parseInt(panel.parentElement.parentElement.style.maxHeight, 10);
          newHeightList += panel.scrollHeight;
          panel.parentElement.parentElement.style.maxHeight = newHeightList + "px"; 
          
      }
      
  });
}

}


