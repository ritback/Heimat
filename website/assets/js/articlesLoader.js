/* Set the width of the sidebar to 250px and the left margin of the page content to 250px */
function openNav() {
  document.getElementById("sidebarNav").style.width = "250px";
}

/* Set the width of the sidebar to 0 and the left margin of the page content to 0 */
function closeNav() {
  document.getElementById("sidebarNav").style.width = "0";
}


/* Set the width of the sidebar to 250px and the left margin of the page content to 250px */
function openAbout() {
  document.getElementById("aboutPanel").style.width = "100%";
}

/* Set the width of the sidebar to 0 and the left margin of the page content to 0 */
function closeAbout() {
  document.getElementById("aboutPanel").style.width = "0";
}


/******************************************************************************/


let numArticleToLoad = 0;
let numArticleLoaded = 0;
        
let request = new XMLHttpRequest();

request.open('GET', '../../articles/filelist.html', true);

request.onload = function() {
    if (request.status >= 200 && request.status < 400) {
        
        let resp = request.responseText;
        resp.replace(/^\s*[\r\n]/gm, "");
        let filenames = resp.split('\n');
        
        for (let i = 0; i < filenames.length; ++i){
            filenames[i].replace(/^\s*[\r\n]/gm, "");
            if (filenames[i] && filenames[i] !== ""){
                
                numArticleToLoad += 1;
                let filerequest = new XMLHttpRequest();
    
                filerequest.open('GET', '../../articles/' + filenames[i], true);
        
                filerequest.onload = function() {
                    if (filerequest.status >= 200 && filerequest.status < 400) {
                        var articleContent = filerequest.responseText;
                
                        let articleElement = parseArticleFile(articleContent);
                        addArticlesToList(articleElement);
                    }
                    
                    numArticleLoaded += 1;
                    checkToSortArticleList();
                }
                
                filerequest.send();
            }
        }
    }
};

request.send();

//
function checkToSortArticleList(){
    if(numArticleLoaded === numArticleToLoad) {
        displayVisibleArticleListCorrectly(".articleElement");
        
        let articleLists = document.querySelectorAll(".articleList");
        // add an element as bottom margin for the lists
        for (let i = 0; i < articleLists.length; ++i){
            
            
            let articleListsCloseButton=document.createElement('a');
            articleListsCloseButton.classList.add("articleListsCloseButton");
            articleListsCloseButton.innerHTML = "×";
            
            
            let articleListsSeparator=document.createElement('div');
            articleListsSeparator.classList.add("articleListsSeparator");
            articleListsSeparator.appendChild(articleListsCloseButton);
            articleListsSeparator.addEventListener("click", function(){
                let ListTitle = this.parentElement.parentElement.previousElementSibling;
                ListTitle.scrollIntoView({behavior: "instant", block: "start"});
                let headOffset = document.getElementById("head").getBoundingClientRect().bottom;
                window.scrollBy(0, -headOffset);
                
                closeAllLists()
            });
            
            let articleListsBottomMargin=document.createElement('div');
            articleListsBottomMargin.classList.add("articleListsBottomMargin");
            articleListsBottomMargin.appendChild(articleListsSeparator);
            
            articleLists[i].appendChild(articleListsBottomMargin);
        }
        
        scriptAfterFullLoad();
    }
}


/******************************************************************************/


function parseArticleFile(articleContent){
    // transform string to DOM documents
    let htmlObject = document.createElement('div');
    htmlObject.innerHTML = articleContent;
    
    // get elements
    let title = htmlObject.querySelector("h2");
    let subTitle = htmlObject.querySelector("h3");
    let panelTextContent = htmlObject.querySelector(".panelTextContent");
    
    //First image will be the button image
    let images = htmlObject.querySelectorAll("img");
    let videos = htmlObject.querySelectorAll("iframe");
    
    //First image will be the button image
    let tags = htmlObject.querySelector("#tags");
    
    // ---------------------------------------------------------------
    // ---------------------------------------------------------------
    // Build the html structure
    
    // ---------------------------------------------------------------
    // AccordionButton Creation
    // titles creation
    let articleTitleContent=document.createElement('div');
    articleTitleContent.classList.add("articleTitleContent");
    articleTitleContent.appendChild(title);
    articleTitleContent.appendChild(subTitle);
    
    
    let articleTitle=document.createElement('div');
    articleTitle.classList.add("articleTitle");
    articleTitle.appendChild(articleTitleContent);
    
    // title Media creation
    let articleTitleMediaFrame=document.createElement('div')
    articleTitleMediaFrame.classList.add("articleTitleMediaFrame");
    articleTitleMediaFrame.appendChild(images[0]);
    
    let articleTitleMediaContainer=document.createElement('div');
    articleTitleMediaContainer.classList.add("articleTitleMediaContainer");
    articleTitleMediaContainer.appendChild(articleTitleMediaFrame);
    
    // Accordion title creation
    let accordionTitleButton=document.createElement('button');
    accordionTitleButton.classList.add("accordionTitleButton");
    accordionTitleButton.appendChild(articleTitle);
    accordionTitleButton.appendChild(articleTitleMediaContainer);
    
    // ---------------------------------------------------------------                    
    // Panel
    //text content
    let panelText=document.createElement('div');
    panelText.classList.add("panelText");
    panelText.appendChild(panelTextContent);
    
    
    // media content
    // -----------------------------------------------------------------------
     
    let panelMediaContainer=document.createElement('article')
    panelMediaContainer.classList.add("panelMediaContainer");
    
    // place videos at first
    for (let i = 0; i < videos.length; ++i){
        
        let panelMediaFrame=document.createElement('div');
        panelMediaFrame.classList.add("panelMediaFrame");
        panelMediaFrame.appendChild(videos[i]);
        
        panelMediaContainer.appendChild(panelMediaFrame);
    }
    
    // then images
    // first image isn't to be set in the panel, just in fancy box
    let firstImageFancybox=document.createElement('a');
    firstImageFancybox.classList.add("fancybox");
    firstImageFancybox.rel = title.innerHTML;
    firstImageFancybox.href = images[0].src;
    panelMediaContainer.appendChild(firstImageFancybox);
    
    for (let i =1; i < images.length; ++i){
        
        let fancybox=document.createElement('a');
        fancybox.classList.add("fancybox");
        fancybox.rel = title.innerHTML;
        fancybox.href = images[i].src;
        fancybox.appendChild(images[i]);
        
        let panelMediaFrame=document.createElement('div');
        panelMediaFrame.classList.add("panelMediaFrame");
        panelMediaFrame.appendChild(fancybox);
        
        panelMediaContainer.appendChild(panelMediaFrame);
    }
    
    
    
    
    
    
    // -----------------------------------------------------------------------
    // Panel content
    let panelContent=document.createElement('article');
    panelContent.classList.add("panelContent");
    panelContent.appendChild(panelText);
    panelContent.appendChild(panelMediaContainer);
    
    
    
    // adding the margin under the panel
    let panelBottomMargin=document.createElement('div');
    panelBottomMargin.classList.add("panelBottomMargin");
    
    let panel=document.createElement('div');
    panel.classList.add("panel");
    panel.appendChild(panelContent);
    panel.appendChild(panelBottomMargin);
    
    
    // List element creation
    let articleElement=document.createElement('li');
    articleElement.classList.add("articleElement");
    
    let strTitle = title.innerHTML;
    articleElement.id = strTitle.replace(/\s+/g, '');
    
    let tagsStr = tags.innerHTML.split(' ')
    for (let i = 0; i < tagsStr.length; i++ ){ 
        articleElement.classList.add(tagsStr[i]);
    }
    articleElement.appendChild(accordionTitleButton);
    articleElement.appendChild(panel);
    
    return articleElement;
    
    
}

/******************************************************************************/


function addArticlesToList(articleElement){
    for (let i = 0; i < articleElement.classList.length; ++i) { 
        if (articleElement.classList[i] == "art") {
            document.getElementById("artList").appendChild(articleElement.cloneNode(true));
        }
        if (articleElement.classList[i] == "conception") {
            document.getElementById("conceptionList").appendChild(articleElement.cloneNode(true));
        }
        if (articleElement.classList[i] == "graphic") {
            document.getElementById("graphicList").appendChild(articleElement.cloneNode(true));
        }
        if (articleElement.classList[i] == "carpentry") {
            document.getElementById("carpentryList").appendChild(articleElement.cloneNode(true));
        }
    }
        
}


/******************************************************************************/



    // hide all articles
function hideAllArticles()
{
    var allArticleElements = document.querySelectorAll(".articleElement");
    var articleElementsNbr = allArticleElements.length;

    for (var i = 0; i < articleElementsNbr; i++)
    {
        allArticleElements[i].style.display = "none";
    }
}

    // display all articles
function displayAllArticles()
{
    var allArticleElements = document.querySelectorAll(".articleElement");
    var articleElementsNbr = allArticleElements.length;

    for (var i = 0; i < articleElementsNbr; i++)
    {
        allArticleElements[i].style.display = "block";
    }
}


function displayVisibleArticleListCorrectly(tag)
{
    hideAllArticles();
    
    // place correctly
    var visibleArticleElements = document.querySelectorAll(tag);
    var visibleArticleElementsNbr = visibleArticleElements.length;
    
	for (var i = 0; i < visibleArticleElementsNbr; i++)
	{
        visibleArticleElements[i].style.display = "block";
        
        var titleContent = visibleArticleElements[i].querySelector(".accordionTitleButton");
        var panelContent = visibleArticleElements[i].querySelector(".panelContent");
        if (i%2==1)
        {
            titleContent.style.flexDirection  = "row-reverse";
            
            var titleTextContent = titleContent.querySelector(".articleTitleContent");
            titleTextContent.style.marginRight = "auto";
            titleTextContent.style.marginLeft = "0";
            titleTextContent.style.textAlign = "left";
                
            panelContent.style.flexDirection  = "row-reverse";
        }
        else
        {
            titleContent.style.flexDirection  = "row";
            
            var titleTextContent = titleContent.querySelector(".articleTitleContent");
            titleTextContent.style.marginRight = "0";
            titleTextContent.style.marginLeft = "auto";
            titleTextContent.style.textAlign = "right";
            
            panelContent.style.flexDirection  = "row";
        }
        
    }
    
    closeNav();
    
}


