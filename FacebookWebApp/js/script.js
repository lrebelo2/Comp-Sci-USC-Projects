$(document).ready(function () {
    $("#pBar").css("visibility", "hidden");
    $("#pBarD1").css("display", "none");
    $("#pBarD2").css("display", "none");
    $("#tCtrl").css("display", "none");
    $("#favsharebtn").css("display", "none");
    $("#detDiv").css("display", "none");
    clearstorage();
    var w = $(window).width() < 500 ? "100%" : "16.666667%";
    $(".nav-tabs > li").css("width", w);
    $.ajaxSetup({
        cache: true
    });
    $.getScript("//connect.facebook.net/en_US/sdk.js", function () {
        FB.init({
            appId: "1191416027640633"
            , version: "v2.8" // or v2.1, v2.2, v2.3, ...
        });
        $("#loginbutton,#feedbutton").removeAttr("disabled");
        FB.getLoginStatus(function () {
            //statuscalback
        });
    });
    angular.element($("#tCtrl")).scope().updatefavorites();
    $("#clear").click(function () {
        //function to clear form and tables
        $("#keyword").val("");
        $("#pBar").css("visibility", "hidden");
        $("#tCtrl").css("display", "none");
    });
});
$(window).resize(function () {
    var w = $(window).width() < 500 ? "100%" : "16.666667%";
    $(".nav-tabs > li").css("width", w);
    $(".table").css("width", $("#header").css("width"));
    $("#detDiv").css("width", $("#TabsTables").css("width"));
});
$(window).on("orientationchange", function () {
    $(".table").css("width", $("#TabsTables").css("width"));
    var w = $(window).width() < 500 ? "100%" : "16.666667%";
    $(".nav-tabs > li").css("width", w);
    $("#detDiv").css("width", $("#TabsTables").css("width"));
});
var app = angular.module("myApp", []);
app.controller("tCtrl", ["$scope", "$http", function ($scope, $http, $location) {
    $scope.requestHTTP = function (key, lat, long) {
            $scope.key = key;
            $scope.lat = lat;
            $scope.long = long;
            $("#detDiv").animate({
                width: "0px"
            }, 200, function () {
                $(this).hide();
                $("#results").animate({
                    width: $(window).width()
                }, 200, function () {
                    $(this).show();
                });
            });
            $http.get("/index.php?keyword=" + key + "&lat=34.0216685&long=-118.2826306").then(function success(data) {
                if (angular.fromJson(data.data.users)) {
                    $scope.userdata = angular.fromJson(data.data.users).data;
                    $scope.userdata.type = 'users';
                    updateS($scope.userdata);
                }
                if (angular.fromJson(data.data.users).paging) {
                    $scope.next_users = angular.fromJson(data.data.users).paging.next ? angular.fromJson(data.data.users).paging.next : undefined;
                    $scope.prev_users = angular.fromJson(data.data.users).paging.previous ? angular.fromJson(data.data.users).paging.previous : undefined;
                }
                if (angular.fromJson(data.data.pages)) {
                    $scope.pagesdata = angular.fromJson(data.data.pages).data;
                    $scope.pagesdata.type = 'pages';
                    updateS($scope.pagesdata);
                }
                if (angular.fromJson(data.data.pages).paging) {
                    $scope.next_pages = angular.fromJson(data.data.pages).paging.next ? angular.fromJson(data.data.pages).paging.next : undefined;
                    $scope.prev_pages = angular.fromJson(data.data.pages).paging.previous ? angular.fromJson(data.data.pages).paging.previous : undefined;
                }
                if (angular.fromJson(data.data.events)) {
                    $scope.eventsdata = angular.fromJson(data.data.events).data;
                    $scope.eventsdata.type = 'events';
                    updateS($scope.eventsdata);
                }
                if (angular.fromJson(data.data.events).paging) {
                    $scope.next_events = angular.fromJson(data.data.events).paging.next ? angular.fromJson(data.data.events).paging.next : undefined;
                    $scope.prev_events = angular.fromJson(data.data.events).paging.previous ? angular.fromJson(data.data.events).paging.previous : undefined;
                }
                if (angular.fromJson(data.data.groups)) {
                    $scope.groupsdata = angular.fromJson(data.data.groups).data;
                    $scope.groupsdata.type = 'groups';
                    updateS($scope.groupsdata);
                }
                if (angular.fromJson(data.data.groups).paging) {
                    $scope.next_groups = angular.fromJson(data.data.groups).paging.next ? angular.fromJson(data.data.groups).paging.next : undefined;
                    $scope.prev_groups = angular.fromJson(data.data.groups).paging.previous ? angular.fromJson(data.data.groups).paging.previous : undefined;
                }
                if (angular.fromJson(data.data.places)) {
                    $scope.placesdata = angular.fromJson(data.data.places).data;
                    $scope.placesdata.type = 'places';
                    updateS($scope.placesdata);
                }
                if (angular.fromJson(data.data.places).paging) {
                    $scope.next_places = angular.fromJson(data.data.places).paging.next ? angular.fromJson(data.data.places).paging.next : undefined;
                    $scope.prev_places = angular.fromJson(data.data.places).paging.previous ? angular.fromJson(data.data.places).paging.previous : undefined;
                }
                updateButtons($scope);
                $("#pBar").css("display", "none");
                $("#tCtrl").css("display", "block");
                $(".table").css("width", $("#TabsTables").css("width"));
            }, function error(data) {
                console.log(data);
            });
        }
        //next(link,type) works for next and previous buttons
    $scope.next = function (link, type) {
        if (link) {
            $http.get(link).then(function successN(data) {
                if (type == "users") {
                    $scope.userdata = data.data.data;
                    updateS($scope.userdata);
                    $scope.next_users = data.data.paging.next;
                    $scope.prev_users = data.data.paging.previous;
                }
                else if (type == "pages") {
                    $scope.pagesdata = data.data.data;
                    updateS($scope.pagesdata);
                    $scope.next_pages = data.data.paging.next;
                    $scope.prev_pages = data.data.paging.previous;
                }
                else if (type == "events") {
                    $scope.eventsdata = data.data.data;
                    updateS($scope.eventsdata);
                    $scope.next_events = data.data.paging.next;
                    $scope.prev_events = data.data.paging.previous;
                }
                else if (type == "places") {
                    $scope.placesdata = data.data.data;
                    updateS($scope.placesdata);
                    $scope.next_places = data.data.paging.next;
                    $scope.prev_places = data.data.paging.previous;
                }
                else if (type == "groups") {
                    $scope.groupsdata = data.data.data;
                    updateS($scope.groupsdata);
                    $scope.next_groups = data.data.paging.next;
                    $scope.prev_groups = data.data.paging.previous;
                }
                updateButtons($scope);
                $("table").css("width", $("rootDiv").width());
            }, function errorN(data) {
                alert("There was a problem with requesting the next page.\nError: " + data.status + ", " + data.statusText);
            });
        }
        else {
            console.log("Pagination link not defined");
        }
    }
    $scope.changeView = function (x, type) {
        $scope.picchange = x.picture.data.url;
        $scope.namechange = x.name;
        $scope.idchange = x.id;
        x.type = type;
        $scope.xchange = x;
        var id = x.id;
        var pic = x.picture.data.url;
        $("#errmsgP").hide();
        $("#results").animate({
            width: "0px"
        }, 200, function () {
            $(this).hide();
            $("#detDiv").animate({
                width: $(window).width()
            }, 200, function () {
                $(this).show();
            });
        });
        $("#favsharebtn").css("display", "block");
        $("#pBarD1").css("display", "block");
        $("#pBarD2").css("display", "block");
        if (type == "events") {
            var url = "https://graph.facebook.com/v2.8/" + id + "?fields=name,posts.limit(5)&access_token=";
        }
        else {
            var url = "https://graph.facebook.com/v2.8/" + id + "?fields=name,albums.limit(5){name,photos.limit(2){name,picture}},posts.limit(5)&access_token=";
        }
        $http.get(url).then(function successD(data) {
            if (data.data.albums) {
                $("#pBarD1").css("display", "none");
                $("#errmsgA").css("display", "none");
                //update album pics with high-res version
                for (i = 0; i < data.data.albums.data.length; i++) {
                    if (data.data.albums.data[i].photos) {
                        for (j = 0; j < data.data.albums.data[i].photos.data.length; j++) {
                            var pic_id = data.data.albums.data[i].photos.data[j].id;
                            data.data.albums.data[i].photos.data[j].picture = "https://graph.facebook.com/v2.8/" + pic_id + "/picture?access_token=";
                        }
                    }
                    else {
                        //if album does not have pictures
                    }
                }
                $scope.detailsAlbums = data.data.albums.data;
            }
            else {
                $("#pBarD1").css("display", "none");
                $scope.detailsAlbums = "";
                $("#albumpanel").css("display", "none");
                $("#errmsgA").css("display", "block");
            }
            if (data.data.posts) {
                $("#errmsgP").css("display", "none");
                $("#pBarD2").css("display", "none");
                $scope.detailsPosts = data.data.posts.data;
                for (i = 0; i < $scope.detailsPosts.length; i++) {
                    var time = moment(data.data.posts.data[1].created_time).format("YYYY-MM-DD hh:mm:ss");
                    $scope.detailsPosts[i].time = time;
                }
                $scope.detailsPosts.name = data.data.name;
                $scope.detailsPosts.pic = pic;
            }
            else {
                $("#pBarD2").css("display", "none");
                $scope.detailsPosts = "";
                $("#postpanel").css("display", "none");
                $("#errmsgP").css("display", "block");
            }
            //check storage
            if (localStorage.getItem(id) != null) {
                $("#starbtndetails").removeClass("glyphicon-star-empty")
                $("#starbtndetails").addClass("glyphicon-star");
            }
            else {
                $("#starbtndetails").removeClass("glyphicon-star");
                $("#starbtndetails").addClass("glyphicon-star-empty");
            }
            angular.element($("#tCtrl")).scope().updatefavorites();
            updateS($scope.userdata);
            updateS($scope.pagesdata);
            updateS($scope.eventsdata);
            updateS($scope.groupsdata);
            updateS($scope.placesdata);
        }, function errorD(data) {
            alert("There was a problem with requesting the next page.\nError: " + data.status + ", " + data.statusText);
        });
    }
    $scope.changeBack = function () {
        $("#detDiv").animate({
            width: "0px"
        }, 200, function () {
            $(this).hide();
            $("#results").animate({
                width: $(window).width()
            }, 200, function () {
                $(this).show();
            });
        });
        updateS($scope.userdata);
        updateS($scope.pagesdata);
        updateS($scope.eventsdata);
        updateS($scope.groupsdata);
        updateS($scope.placesdata);
    }
    $scope.share = function () {
        if (FB) {
            FB.ui({
                app_id: "1191416027640633"
                , method: "feed"
                , link: window.location.href
                , picture: $scope.picchange
                , name: $scope.namechange
                , caption: "FB SEARCH FROM USC CSCI571"
            }, function (response) {
                if (response && !response.error_message) {
                    alert("Posted Successfully");
                }
                else {
                    alert("Not Posted");
                }
            });
        }
        else console.log("There was a problem loading Facebook SDK");
    }
    $scope.favorite = function (y, type) {
        var key = y.id;
        y.type = type;
        if (localStorage.getItem(key) == null) {
            var x = angular.toJson(y);
            localStorage.setItem(key, x);
            //set star starbtndetails
            $(".starbtn" + key).children().addClass("glyphicon-star");
            $(".starbtn" + key).children().removeClass("glyphicon-star-empty");
        }
        else {
            localStorage.removeItem(key);
            //reset star starbtndetails
            $(".starbtn" + key).children().removeClass("glyphicon-star");
            $(".starbtn" + key).children().addClass("glyphicon-star-empty");
        }
        angular.element($("#tCtrl")).scope().updatefavorites();
    }
    $scope.detailsS = function () {
        var y = $scope.xchange;
        var key = y.id;
        if (localStorage.getItem(key) == null) {
            var x = angular.toJson(y);
            localStorage.setItem(key, x);
            //set star starbtndetails
            $("#starbtndetails").removeClass("glyphicon-star-empty");
            $("#starbtndetails").addClass("glyphicon-star");
        }
        else {
            localStorage.removeItem(key);
            //reset star starbtndetails
            $("#starbtndetails").removeClass("glyphicon-star");
            $("#starbtndetails").addClass("glyphicon-star-empty");
        }
        angular.element($("#tCtrl")).scope().updatefavorites();
        updateS($scope.userdata);
        updateS($scope.pagesdata);
        updateS($scope.eventsdata);
        updateS($scope.groupsdata);
        updateS($scope.placesdata);
    }
    $scope.updatefavorites = function () {
        var re = /^\d+$/;
        $scope.favdata = [];
        for (i = 0; i < localStorage.length; i++) {
            var index = localStorage.key(i);
            //to not use any other data in local storage thats not from this app
            if (index.match(re)) {
                $scope.favdata.push(angular.fromJson(localStorage.getItem(index)));
            }
        }
        if ($scope.userdata) {
            updateS($scope.userdata);
            updateS($scope.pagesdata);
            updateS($scope.eventsdata);
            updateS($scope.groupsdata);
            updateS($scope.placesdata);
            
        }
        //console.log($scope.favdata);                              
    }
    $scope.removefavorite = function (id) {
        localStorage.removeItem(id);
        angular.element($("#tCtrl")).scope().updatefavorites();
        updateS($scope.userdata);
        updateS($scope.pagesdata);
        updateS($scope.eventsdata);
        updateS($scope.groupsdata);
        updateS($scope.placesdata);
    }
    }]);

function updateS(data) {
    for (i = 0; i < data.length; i++) {
        var key = data[i].id;
        if (localStorage.getItem(key) == null) {
            //is not there
            data[i].classStar = "glyphicon-star-empty";
        }
        else {
            //is there
            data[i].classStar = "glyphicon-star";
        }
    }
}

function requestToAngularHTTP(lat, long) {
    angular.element($("#tCtrl")).scope().requestHTTP($("#keyword").val(), lat, long);
}

function toggle(id) {
    var num = id.replace(/^\D+/g, "");
    if ($("#AlbumBody" + num).children()[0].firstElementChild.currentSrc == "") {
        $("#AlbumBody" + num).children()[0].firstElementChild.remove();
    }
    if ($("#AlbumBody" + num).children()[0].lastElementChild.currentSrc == "") {
        $("#AlbumBody" + num).children()[0].lastElementChild.remove();
    }
    if ($("#AlbumBody" + num).css("display") == undefined) {
        $("#AlbumBody" + num).css("display", "none");
    }
    else if ($("#AlbumBody" + num).css("display") == "none") {
        $("#AlbumBody" + num).css("display", "block");
    }
    else if ($("#AlbumBody" + num).css("display") == "block") {
        $("#AlbumBody" + num).css("display", "none");
    }
}

function hideA() {
    if ($("#albumbody").css("display") == undefined) {
        $("#albumbody").css("display", "none");
    }
    else if ($("#albumbody").css("display") == "none") {
        $("#albumbody").css("display", "block");
    }
    else if ($("#albumbody").css("display") == "block") {
        $("#albumbody").css("display", "none");
    }
}

function hideP() {
    if ($("#postsbody").css("display") == undefined) {
        $("#postsbody").css("display", "none");
    }
    else if ($("#postsbody").css("display") == "none") {
        $("#postsbody").css("display", "block");
    }
    else if ($("#postsbody").css("display") == "block") {
        $("#postsbody").css("display", "none");
    }
}

function clearstorage() {
    for (i = 0; i < localStorage.length - 1; i++) {
        var key = localStorage.key(i);
        localStorage.removeItem(key);
    }
}

function updateButtons(scope) {
    $("table").css("width", $("rootDiv").width());
    //users
    if (!scope.next_users) $("#nextbtnusers").hide();
    else $("#nextbtnusers").show();
    if (!scope.prev_users) $("#prevbtnusers").hide();
    else $("#prevbtnusers").show();
    //pages
    if (!scope.next_pages) $("#nextbtnpages").hide();
    else $("#nextbtnpages").show();
    if (!scope.prev_pages) $("#prevbtnpages").hide();
    else $("#prevbtnpages").show();
    //events
    if (!scope.next_events) $("#nextbtnevents").hide();
    else $("#nextbtnevents").show();
    if (!scope.prev_events) $("#prevbtnevents").hide();
    else $("#prevbtnevents").show();
    //groups
    if (!scope.next_groups) $("#nextbtngroups").hide();
    else $("#nextbtngroups").show();
    if (!scope.prev_groups) $("#prevbtngroups").hide();
    else $("#prevbtngroups").show();
    //palces
    if (!scope.next_places) $("#nextbtnplaces").hide();
    else $("#nextbtnplaces").show();
    if (!scope.prev_places) $("#prevbtnplaces").hide();
    else $("#prevbtnplaces").show();
}
app.controller("ctrl", ["$scope", "$http", function ($scope, $http) {
    $scope.requestPHP = function () {
        $("#tCtrl").css("display", "none");
        $("#pBar").css("visibility", "visible");
        $("#pBar").css("display", "block");
        $("#pBarC").css("width", "40%");
        navigator.geolocation.getCurrentPosition(success, error, options);
    }
}]);

function imgOpen(src) {
    s = "<html><head><title>Image</title></head><body><img src=" + src + "></body></hmtl>";
    ImgW = window.open();
    ImgW.document.write(s);
}

function success(pos) {
    var crd = pos.coords;
    var lat = crd.latitude;
    var long = crd.longitude;
    $("#pBarC").css("width", "60%");
    lat = "34.0216685";
    long = "-118.2826306";
    requestToAngularHTTP(lat, long);
};

function error(err) {
    console.warn(`ERROR(${err.code}): ${err.message}`);
        lat = "34.0216685";
    long = "-118.2826306";
    requestToAngularHTTP(lat, long);
};
var options = {
    enableHighAccuracy: true
    , timeout: 5000
};