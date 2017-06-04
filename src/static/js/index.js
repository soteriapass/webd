// ----- Setup: add dummy password text field and add toggle button
$('input[type=password]').each(function(){
  var el = $(this), elPH = el.attr("placeholder");
  
  el.addClass("offPage").before('<input type="text" class="passText" placeholder="' + elPH + '" />');
});

$('form').append('<small><a href="#" class="togglePassText">Toggle Password Visibility</a></small>');


// ----- keep text in sync
$('input[type=password]').keyup(function(){
  var elText = $(this).val();
  $('.passText').val(elText);
});
$('.passText').keyup(function(){
  var elText = $(this).val();
  $('input[type=password]').val(elText);
});

// ----- Toggle button functions
$('a.togglePassText').click(function(e){

  $('input[type=password], .passText').toggleClass("offPage");

  // -- prevent any default actions
  e.preventDefault();

});