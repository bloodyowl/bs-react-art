module Path = {
  type t;
  external make : unit => t = "Path" [@@bs.module "react-art"];
  external move : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external moveTo : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external line : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external lineTo : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external curve : c1x::int => c1y::int => c2x::int => c2y::int => ex::int => ey::int => t =
    "" [@@bs.send.pipe : t];
  external curveTo : c1x::int => c1y::int => c2x::int => c2y::int => ex::int => ey::int => t =
    "" [@@bs.send.pipe : t];
  external jsArc :
    x::int =>
    y::int =>
    rx::int =>
    ry::int =>
    outer::int =>
    counterClockwise::Js.boolean =>
    rotation::int =>
    t =
    "arc" [@@bs.send.pipe : t];
  let arc ::x ::y ::rx ::ry ::outer ::counterClockwise ::rotation path =>
    jsArc
      ::x
      ::y
      ::rx
      ::ry
      ::outer
      counterClockwise::(Js.Boolean.to_js_boolean counterClockwise)
      ::rotation
      path;
  external jsArcTo :
    x::int =>
    y::int =>
    rx::int =>
    ry::int =>
    outer::int =>
    counterClockwise::Js.boolean =>
    rotation::int =>
    t =
    "arcTo" [@@bs.send.pipe : t];
  let arcTo ::x ::y ::rx ::ry ::outer ::counterClockwise ::rotation path =>
    jsArcTo
      ::x
      ::y
      ::rx
      ::ry
      ::outer
      counterClockwise::(Js.Boolean.to_js_boolean counterClockwise)
      ::rotation
      path;
  external counterArc : x::int => y::int => rx::int => ry::int => outer::int => t =
    "" [@@bs.send.pipe : t];
  external counterArcTo : x::int => y::int => rx::int => ry::int => outer::int => t =
    "" [@@bs.send.pipe : t];
  external close : t = "" [@@bs.send.pipe : t];
};

module Transform = {
  type t;
  type point = {
    x: int,
    y: int
  };
  type jsPoint = Js.t {. x : int, y : int};
  let jsPointToReason (jsPoint: jsPoint) => {x: jsPoint##x, y: jsPoint##y};
  external make : unit => t = "Transform" [@@bs.module "react-art"] [@@bs.new];
  external makeWithArgs : xx::int => yx::int => xy::int => yy::int => x::int => y::int => unit => t =
    "Transform" [@@bs.module "react-art"] [@@bs.new];
  external transform : xx::int => yx::int => xy::int => yy::int => x::int => y::int => unit => t =
    "" [@@bs.send.pipe : t];
  external translate : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external move : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external moveTo : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external scale : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external scaleTo : x::int => y::int => t = "" [@@bs.send.pipe : t];
  external rotate : deg::int => x::int => y::int => t = "" [@@bs.send.pipe : t];
  external rotateTo : deg::int => x::int => y::int => t = "" [@@bs.send.pipe : t];
  external resizeTo : width::int => height::int => t = "" [@@bs.send.pipe : t];
  external jsPoint : x::int => y::int => jsPoint = "point" [@@bs.send.pipe : t];
  external jsInversePoint : x::int => y::int => jsPoint = "inversePoint" [@@bs.send.pipe : t];
  let point ::x ::y t => jsPoint ::x ::y t |> jsPointToReason;
  let inversePoint ::x ::y t => jsInversePoint ::x ::y t |> jsPointToReason;
};

module Pattern = {
  type t;
  external make : url::string => width::int => height::int => left::int => top::int => t =
    "Pattern" [@@bs.module "react-art"] [@@bs.new];
};

module LinearGradient = {
  type t;
  external makeFromArrayStops :
    stops::array string => x1::int => y1::int => x2::int => y2::int => t =
    "LinearGradient" [@@bs.module "react-art"] [@@bs.new];
  /* TODO: convert from a (pos, color) tuple to Js.Obj */
  external makeFromJsStops : stops::Js.t {.} => x1::int => y1::int => x2::int => y2::int => t =
    "LinearGradient" [@@bs.module "react-art"] [@@bs.new];
};

module RadialGradient = {
  type t;
  external makeFromArrayStops :
    stops::array string => fx::int => fy::int => rx::int => ry::int => cx::int => cy::int => t =
    "RadialGradient" [@@bs.module "react-art"] [@@bs.new];
  /* TODO: convert from a (pos, color) tuple to Js.Obj */
  external makeFromJsStops :
    stops::Js.t {.} => fx::int => fy::int => rx::int => ry::int => cx::int => cy::int => t =
    "RadialGradient" [@@bs.module "react-art"] [@@bs.new];
};

external surface : ReasonReact.reactClass = "Surface" [@@bs.module "react-art"];

module Surface = {
  let make
      width::(width: int)
      height::(height: int)
      className::(className: option string)=?
      style::(style: option ReactDOMRe.style)=?
      role::(role: option string)=?
      title::(title: option string)=?
      tabIndex::(tabIndex: option int)=?
      ::draggable=false
      children =>
    ReasonReact.wrapJsForReason
      reactClass::surface
      props::{
        "width": width,
        "height": height,
        "className": Js.Null.from_opt className,
        "style": Js.Null.from_opt style,
        "tabIndex": Js.Null.from_opt tabIndex,
        "role": Js.Null.from_opt role,
        "title": Js.Null.from_opt title,
        "draggable": Js.Boolean.to_js_boolean draggable
      }
      children;
};

external text : ReasonReact.reactClass = "Text" [@@bs.module "react-art"];

module Text = {
  let make
      font::(font: option string)=?
      fontSize::(fontSize: option int)=?
      fontStyle::(fontStyle: option string)=?
      fontVariant::(fontVariant: option int)=?
      fontWeight::(fontWeight: option string)=?
      fontFamily::(fontFamily: option string)=?
      alignment::(alignment: option string)=?
      path::(path: option Path.t)=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::text
      props::{
        "font": Js.Null.from_opt font,
        "fontSize": Js.Null.from_opt fontSize,
        "fontStyle": Js.Null.from_opt fontStyle,
        "fontVariant": Js.Null.from_opt fontVariant,
        "fontWeight": Js.Null.from_opt fontWeight,
        "fontFamily": Js.Null.from_opt fontFamily,
        "alignment": Js.Null.from_opt alignment,
        "path": Js.Null.from_opt path
      }
      children;
};
