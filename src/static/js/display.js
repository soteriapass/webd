function swapInput(tag, type) {
  var el = document.createElement('input');
  el.id = tag.id;
  el.type = type;
  el.name = tag.name;
  el.value = tag.value; 
  tag.parentNode.insertBefore(el, tag);
  tag.parentNode.removeChild(tag);
}

function toggle_password(target, target2){
    var d = document;
    var tag = d.getElementById(target);
    var tag2 = d.getElementById(target2);

    if (tag2.innerHTML == 'Show'){

        swapInput(tag, 'text');
        tag2.innerHTML = 'Hide';

    } else {
        swapInput(tag, 'password');   
        tag2.innerHTML = 'Show';
    }
}