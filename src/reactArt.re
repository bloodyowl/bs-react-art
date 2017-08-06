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

let stopsToJs stops =>
  List.fold_left
    (
      fun dict (key, value) => {
        Js.Dict.set dict key value;
        dict
      }
    )
    (Js.Dict.empty ())
    stops;

module LinearGradient = {
  type t;
  external makeFromArrayStops :
    stops::array string => x1::int => y1::int => x2::int => y2::int => t =
    "LinearGradient" [@@bs.module "react-art"] [@@bs.new];
  external makeFromJsStops :
    stops::Js.Dict.t string => x1::int => y1::int => x2::int => y2::int => t =
    "LinearGradient" [@@bs.module "react-art"] [@@bs.new];
  let make ::stops ::x1 ::y1 ::x2 ::y2 =>
    makeFromJsStops stops::(stopsToJs stops) ::x1 ::y1 ::x2 ::y2;
};

module RadialGradient = {
  type t;
  external makeFromArrayStops :
    stops::array string => fx::int => fy::int => rx::int => ry::int => cx::int => cy::int => t =
    "RadialGradient" [@@bs.module "react-art"] [@@bs.new];
  external makeFromJsStops :
    stops::Js.Dict.t string => fx::int => fy::int => rx::int => ry::int => cx::int => cy::int => t =
    "RadialGradient" [@@bs.module "react-art"] [@@bs.new];
  let make ::stops ::fx ::fy ::rx ::ry ::cx ::cy =>
    makeFromJsStops stops::(stopsToJs stops) ::fx ::fy ::rx ::ry ::cx ::cy;
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

type fill =
  | String string
  | LinearGradient LinearGradient.t
  | RadialGradient RadialGradient.t
  | Pattern Pattern.t;

type jsFill;

external stringToJsFill : string => jsFill = "%identity";

external linearGradientToJsFill : LinearGradient.t => jsFill = "%identity";

external radialGradientToJsFill : RadialGradient.t => jsFill = "%identity";

external patternToJsFill : Pattern.t => jsFill = "%identity";

let fillToJs fill =>
  switch fill {
  | Some fill =>
    switch fill {
    | String v => Js.Null.return (stringToJsFill v)
    | LinearGradient v => Js.Null.return (linearGradientToJsFill v)
    | RadialGradient v => Js.Null.return (radialGradientToJsFill v)
    | Pattern v => Js.Null.return (patternToJsFill v)
    }
  | None => Js.Null.empty
  };

external group : ReasonReact.reactClass = "Group" [@@bs.module "react-art"];

module Group = {
  let make
      width::(width: option int)=?
      height::(height: option int)=?
      scaleX::(scaleX: option float)=?
      scaleY::(scaleY: option float)=?
      scale::(scale: option float)=?
      x::(x: option int)=?
      y::(y: option int)=?
      originX::(originX: option int)=?
      originY::(originY: option int)=?
      transform::(transform: option Transform.t)=?
      cursor::(cursor: option string)=?
      opacity::(opacity: option float)=?
      ::visible=true
      onMouseMove::(onMouseMove: option (DomRe.MouseEvent.t => unit))=?
      onMouseOver::(onMouseOver: option (DomRe.MouseEvent.t => unit))=?
      onMouseOut::(onMouseOut: option (DomRe.MouseEvent.t => unit))=?
      onMouseUp::(onMouseUp: option (DomRe.MouseEvent.t => unit))=?
      onMouseDown::(onMouseDown: option (DomRe.MouseEvent.t => unit))=?
      onClick::(onClick: option (DomRe.MouseEvent.t => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::group
      props::{
        "width": Js.Null_undefined.from_opt width,
        "height": Js.Null_undefined.from_opt height,
        "scaleX": Js.Null_undefined.from_opt scaleX,
        "scaleY": Js.Null_undefined.from_opt scaleY,
        "scale": Js.Null_undefined.from_opt scale,
        "x": Js.Null_undefined.from_opt x,
        "y": Js.Null_undefined.from_opt y,
        "originX": Js.Null_undefined.from_opt originX,
        "originY": Js.Null_undefined.from_opt originY,
        "transform": Js.Null_undefined.from_opt transform,
        "cursor": Js.Null_undefined.from_opt cursor,
        "opacity": Js.Null_undefined.from_opt opacity,
        "visible": Js.Boolean.to_js_boolean visible,
        "onMouseMove": Js.Null_undefined.from_opt onMouseMove,
        "onMouseOver": Js.Null_undefined.from_opt onMouseOver,
        "onMouseOut": Js.Null_undefined.from_opt onMouseOut,
        "onMouseUp": Js.Null_undefined.from_opt onMouseUp,
        "onMouseDown": Js.Null_undefined.from_opt onMouseDown,
        "onClick": Js.Null_undefined.from_opt onClick
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
      fill::(fill: option fill)=?
      stroke::(stroke: option string)=?
      strokeWidth::(strokeWidth: option int)=?
      strokeCap::(strokeCap: option string)=?
      strokeJoin::(strokeJoin: option string)=?
      strokeDash::(strokeDash: option string)=?
      scaleX::(scaleX: option float)=?
      scaleY::(scaleY: option float)=?
      scale::(scale: option float)=?
      x::(x: option int)=?
      y::(y: option int)=?
      originX::(originX: option int)=?
      originY::(originY: option int)=?
      transform::(transform: option Transform.t)=?
      cursor::(cursor: option string)=?
      opacity::(opacity: option float)=?
      ::visible=true
      onMouseMove::(onMouseMove: option (DomRe.MouseEvent.t => unit))=?
      onMouseOver::(onMouseOver: option (DomRe.MouseEvent.t => unit))=?
      onMouseOut::(onMouseOut: option (DomRe.MouseEvent.t => unit))=?
      onMouseUp::(onMouseUp: option (DomRe.MouseEvent.t => unit))=?
      onMouseDown::(onMouseDown: option (DomRe.MouseEvent.t => unit))=?
      onClick::(onClick: option (DomRe.MouseEvent.t => unit))=?
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
        "path": Js.Null.from_opt path,
        "fill": fillToJs fill,
        "stroke": Js.Null_undefined.from_opt stroke,
        "strokeWidth": Js.Null_undefined.from_opt strokeWidth,
        "strokeCap": Js.Null_undefined.from_opt strokeCap,
        "strokeJoin": Js.Null_undefined.from_opt strokeJoin,
        "strokeDash": Js.Null_undefined.from_opt strokeDash,
        "scaleX": Js.Null_undefined.from_opt scaleX,
        "scaleY": Js.Null_undefined.from_opt scaleY,
        "scale": Js.Null_undefined.from_opt scale,
        "x": Js.Null_undefined.from_opt x,
        "y": Js.Null_undefined.from_opt y,
        "originX": Js.Null_undefined.from_opt originX,
        "originY": Js.Null_undefined.from_opt originY,
        "transform": Js.Null_undefined.from_opt transform,
        "cursor": Js.Null_undefined.from_opt cursor,
        "opacity": Js.Null_undefined.from_opt opacity,
        "visible": Js.Boolean.to_js_boolean visible,
        "onMouseMove": Js.Null_undefined.from_opt onMouseMove,
        "onMouseOver": Js.Null_undefined.from_opt onMouseOver,
        "onMouseOut": Js.Null_undefined.from_opt onMouseOut,
        "onMouseUp": Js.Null_undefined.from_opt onMouseUp,
        "onMouseDown": Js.Null_undefined.from_opt onMouseDown,
        "onClick": Js.Null_undefined.from_opt onClick
      }
      children;
};

external shape : ReasonReact.reactClass = "Shape" [@@bs.module "react-art"];

module Shape = {
  let make
      d::(d: Path.t)
      width::(width: option int)=?
      height::(height: option int)=?
      fill::(fill: option fill)=?
      stroke::(stroke: option string)=?
      strokeWidth::(strokeWidth: option int)=?
      strokeCap::(strokeCap: option string)=?
      strokeJoin::(strokeJoin: option string)=?
      strokeDash::(strokeDash: option string)=?
      scaleX::(scaleX: option float)=?
      scaleY::(scaleY: option float)=?
      scale::(scale: option float)=?
      x::(x: option int)=?
      y::(y: option int)=?
      originX::(originX: option int)=?
      originY::(originY: option int)=?
      transform::(transform: option Transform.t)=?
      cursor::(cursor: option string)=?
      opacity::(opacity: option float)=?
      ::visible=true
      onMouseMove::(onMouseMove: option (DomRe.MouseEvent.t => unit))=?
      onMouseOver::(onMouseOver: option (DomRe.MouseEvent.t => unit))=?
      onMouseOut::(onMouseOut: option (DomRe.MouseEvent.t => unit))=?
      onMouseUp::(onMouseUp: option (DomRe.MouseEvent.t => unit))=?
      onMouseDown::(onMouseDown: option (DomRe.MouseEvent.t => unit))=?
      onClick::(onClick: option (DomRe.MouseEvent.t => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::shape
      props::{
        "d": d,
        "width": Js.Null_undefined.from_opt width,
        "height": Js.Null_undefined.from_opt height,
        "fill": fillToJs fill,
        "stroke": Js.Null_undefined.from_opt stroke,
        "strokeWidth": Js.Null_undefined.from_opt strokeWidth,
        "strokeCap": Js.Null_undefined.from_opt strokeCap,
        "strokeJoin": Js.Null_undefined.from_opt strokeJoin,
        "strokeDash": Js.Null_undefined.from_opt strokeDash,
        "scaleX": Js.Null_undefined.from_opt scaleX,
        "scaleY": Js.Null_undefined.from_opt scaleY,
        "scale": Js.Null_undefined.from_opt scale,
        "x": Js.Null_undefined.from_opt x,
        "y": Js.Null_undefined.from_opt y,
        "originX": Js.Null_undefined.from_opt originX,
        "originY": Js.Null_undefined.from_opt originY,
        "transform": Js.Null_undefined.from_opt transform,
        "cursor": Js.Null_undefined.from_opt cursor,
        "opacity": Js.Null_undefined.from_opt opacity,
        "visible": Js.Boolean.to_js_boolean visible,
        "onMouseMove": Js.Null_undefined.from_opt onMouseMove,
        "onMouseOver": Js.Null_undefined.from_opt onMouseOver,
        "onMouseOut": Js.Null_undefined.from_opt onMouseOut,
        "onMouseUp": Js.Null_undefined.from_opt onMouseUp,
        "onMouseDown": Js.Null_undefined.from_opt onMouseDown,
        "onClick": Js.Null_undefined.from_opt onClick
      }
      children;
};

external rectangle : ReasonReact.reactClass = "react-art/lib/Rectangle.art" [@@bs.module];

module Rectangle = {
  let make
      width::(width: option int)=?
      height::(height: option int)=?
      radius::(radius: option int)=?
      radiusTopLeft::(radiusTopLeft: option int)=?
      radiusTopRight::(radiusTopRight: option int)=?
      radiusBottomRight::(radiusBottomRight: option int)=?
      radiusBottomLeft::(radiusBottomLeft: option int)=?
      fill::(fill: option fill)=?
      stroke::(stroke: option string)=?
      strokeWidth::(strokeWidth: option int)=?
      strokeCap::(strokeCap: option string)=?
      strokeJoin::(strokeJoin: option string)=?
      strokeDash::(strokeDash: option string)=?
      scaleX::(scaleX: option float)=?
      scaleY::(scaleY: option float)=?
      scale::(scale: option float)=?
      x::(x: option int)=?
      y::(y: option int)=?
      originX::(originX: option int)=?
      originY::(originY: option int)=?
      transform::(transform: option Transform.t)=?
      cursor::(cursor: option string)=?
      opacity::(opacity: option float)=?
      ::visible=true
      onMouseMove::(onMouseMove: option (DomRe.MouseEvent.t => unit))=?
      onMouseOver::(onMouseOver: option (DomRe.MouseEvent.t => unit))=?
      onMouseOut::(onMouseOut: option (DomRe.MouseEvent.t => unit))=?
      onMouseUp::(onMouseUp: option (DomRe.MouseEvent.t => unit))=?
      onMouseDown::(onMouseDown: option (DomRe.MouseEvent.t => unit))=?
      onClick::(onClick: option (DomRe.MouseEvent.t => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::rectangle
      props::{
        "width": Js.Null_undefined.from_opt width,
        "height": Js.Null_undefined.from_opt height,
        "radius": Js.Null_undefined.from_opt radius,
        "radiusTopLeft": Js.Null_undefined.from_opt radiusTopLeft,
        "radiusTopRight": Js.Null_undefined.from_opt radiusTopRight,
        "radiusBottomRight": Js.Null_undefined.from_opt radiusBottomRight,
        "radiusBottomLeft": Js.Null_undefined.from_opt radiusBottomLeft,
        "fill": fillToJs fill,
        "stroke": Js.Null_undefined.from_opt stroke,
        "strokeWidth": Js.Null_undefined.from_opt strokeWidth,
        "strokeCap": Js.Null_undefined.from_opt strokeCap,
        "strokeJoin": Js.Null_undefined.from_opt strokeJoin,
        "strokeDash": Js.Null_undefined.from_opt strokeDash,
        "scaleX": Js.Null_undefined.from_opt scaleX,
        "scaleY": Js.Null_undefined.from_opt scaleY,
        "scale": Js.Null_undefined.from_opt scale,
        "x": Js.Null_undefined.from_opt x,
        "y": Js.Null_undefined.from_opt y,
        "originX": Js.Null_undefined.from_opt originX,
        "originY": Js.Null_undefined.from_opt originY,
        "transform": Js.Null_undefined.from_opt transform,
        "cursor": Js.Null_undefined.from_opt cursor,
        "opacity": Js.Null_undefined.from_opt opacity,
        "visible": Js.Boolean.to_js_boolean visible,
        "onMouseMove": Js.Null_undefined.from_opt onMouseMove,
        "onMouseOver": Js.Null_undefined.from_opt onMouseOver,
        "onMouseOut": Js.Null_undefined.from_opt onMouseOut,
        "onMouseUp": Js.Null_undefined.from_opt onMouseUp,
        "onMouseDown": Js.Null_undefined.from_opt onMouseDown,
        "onClick": Js.Null_undefined.from_opt onClick
      }
      children;
};

external circle : ReasonReact.reactClass = "react-art/lib/Circle.art" [@@bs.module];

module Circle = {
  let make
      radius::(radius: int)
      fill::(fill: option fill)=?
      stroke::(stroke: option string)=?
      strokeWidth::(strokeWidth: option int)=?
      strokeCap::(strokeCap: option string)=?
      strokeJoin::(strokeJoin: option string)=?
      strokeDash::(strokeDash: option string)=?
      scaleX::(scaleX: option float)=?
      scaleY::(scaleY: option float)=?
      scale::(scale: option float)=?
      x::(x: option int)=?
      y::(y: option int)=?
      originX::(originX: option int)=?
      originY::(originY: option int)=?
      transform::(transform: option Transform.t)=?
      cursor::(cursor: option string)=?
      opacity::(opacity: option float)=?
      ::visible=true
      onMouseMove::(onMouseMove: option (DomRe.MouseEvent.t => unit))=?
      onMouseOver::(onMouseOver: option (DomRe.MouseEvent.t => unit))=?
      onMouseOut::(onMouseOut: option (DomRe.MouseEvent.t => unit))=?
      onMouseUp::(onMouseUp: option (DomRe.MouseEvent.t => unit))=?
      onMouseDown::(onMouseDown: option (DomRe.MouseEvent.t => unit))=?
      onClick::(onClick: option (DomRe.MouseEvent.t => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::circle
      props::{
        "radius": radius,
        "fill": fillToJs fill,
        "stroke": Js.Null_undefined.from_opt stroke,
        "strokeWidth": Js.Null_undefined.from_opt strokeWidth,
        "strokeCap": Js.Null_undefined.from_opt strokeCap,
        "strokeJoin": Js.Null_undefined.from_opt strokeJoin,
        "strokeDash": Js.Null_undefined.from_opt strokeDash,
        "scaleX": Js.Null_undefined.from_opt scaleX,
        "scaleY": Js.Null_undefined.from_opt scaleY,
        "scale": Js.Null_undefined.from_opt scale,
        "x": Js.Null_undefined.from_opt x,
        "y": Js.Null_undefined.from_opt y,
        "originX": Js.Null_undefined.from_opt originX,
        "originY": Js.Null_undefined.from_opt originY,
        "transform": Js.Null_undefined.from_opt transform,
        "cursor": Js.Null_undefined.from_opt cursor,
        "opacity": Js.Null_undefined.from_opt opacity,
        "visible": Js.Boolean.to_js_boolean visible,
        "onMouseMove": Js.Null_undefined.from_opt onMouseMove,
        "onMouseOver": Js.Null_undefined.from_opt onMouseOver,
        "onMouseOut": Js.Null_undefined.from_opt onMouseOut,
        "onMouseUp": Js.Null_undefined.from_opt onMouseUp,
        "onMouseDown": Js.Null_undefined.from_opt onMouseDown,
        "onClick": Js.Null_undefined.from_opt onClick
      }
      children;
};

external wedge : ReasonReact.reactClass = "react-art/lib/Wedge.art" [@@bs.module];

module Wedge = {
  let make
      outerRadius::(outerRadius: int)
      startAngle::(startAngle: int)
      endAngle::(endAngle: int)
      innerRadius::(innerRadius: option int)=?
      fill::(fill: option fill)=?
      stroke::(stroke: option string)=?
      strokeWidth::(strokeWidth: option int)=?
      strokeCap::(strokeCap: option string)=?
      strokeJoin::(strokeJoin: option string)=?
      strokeDash::(strokeDash: option string)=?
      scaleX::(scaleX: option float)=?
      scaleY::(scaleY: option float)=?
      scale::(scale: option float)=?
      x::(x: option int)=?
      y::(y: option int)=?
      originX::(originX: option int)=?
      originY::(originY: option int)=?
      transform::(transform: option Transform.t)=?
      cursor::(cursor: option string)=?
      opacity::(opacity: option float)=?
      ::visible=true
      onMouseMove::(onMouseMove: option (DomRe.MouseEvent.t => unit))=?
      onMouseOver::(onMouseOver: option (DomRe.MouseEvent.t => unit))=?
      onMouseOut::(onMouseOut: option (DomRe.MouseEvent.t => unit))=?
      onMouseUp::(onMouseUp: option (DomRe.MouseEvent.t => unit))=?
      onMouseDown::(onMouseDown: option (DomRe.MouseEvent.t => unit))=?
      onClick::(onClick: option (DomRe.MouseEvent.t => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::wedge
      props::{
        "outerRadius": outerRadius,
        "startAngle": startAngle,
        "endAngle": endAngle,
        "innerRadius": Js.Null_undefined.from_opt innerRadius,
        "fill": fillToJs fill,
        "stroke": Js.Null_undefined.from_opt stroke,
        "strokeWidth": Js.Null_undefined.from_opt strokeWidth,
        "strokeCap": Js.Null_undefined.from_opt strokeCap,
        "strokeJoin": Js.Null_undefined.from_opt strokeJoin,
        "strokeDash": Js.Null_undefined.from_opt strokeDash,
        "scaleX": Js.Null_undefined.from_opt scaleX,
        "scaleY": Js.Null_undefined.from_opt scaleY,
        "scale": Js.Null_undefined.from_opt scale,
        "x": Js.Null_undefined.from_opt x,
        "y": Js.Null_undefined.from_opt y,
        "originX": Js.Null_undefined.from_opt originX,
        "originY": Js.Null_undefined.from_opt originY,
        "transform": Js.Null_undefined.from_opt transform,
        "cursor": Js.Null_undefined.from_opt cursor,
        "opacity": Js.Null_undefined.from_opt opacity,
        "visible": Js.Boolean.to_js_boolean visible,
        "onMouseMove": Js.Null_undefined.from_opt onMouseMove,
        "onMouseOver": Js.Null_undefined.from_opt onMouseOver,
        "onMouseOut": Js.Null_undefined.from_opt onMouseOut,
        "onMouseUp": Js.Null_undefined.from_opt onMouseUp,
        "onMouseDown": Js.Null_undefined.from_opt onMouseDown,
        "onClick": Js.Null_undefined.from_opt onClick
      }
      children;
};
